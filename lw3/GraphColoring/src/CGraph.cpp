#include "CGraph.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>
#include <unordered_set>

CGraph::CGraph(const std::map<int, std::set<int>>& adjacencies, const std::vector<std::set<int>>& faces)
{
	for (const auto& [vertex, neighbors] : adjacencies)
	{
		AddVertex(vertex);
		for (int neighbor : neighbors)
		{
			AddEdge(vertex, neighbor);
		}
	}

	for (size_t i = 0; i < faces.size(); ++i)
	{
		std::vector<int> boundaryVertices(faces[i].begin(), faces[i].end());
		AddFace(static_cast<int>(i), boundaryVertices);
	}
}

CGraph::CGraph(const std::vector<std::vector<int>>& adjacencyMatrix)
{
	auto n = adjacencyMatrix.size();
	for (int i = 0; i < n; ++i)
	{
		AddVertex(i + 1);
		for (int j = 0; j < n; ++j)
		{
			if (adjacencyMatrix[i][j] == 1 && i != j)
			{
				AddEdge(i + 1, j + 1);
			}
		}
	}
}

std::unordered_map<int, Vertex> CGraph::GetVertices() const noexcept
{
	return m_vertices;
}

std::vector<Edge> CGraph::GetEdges() const noexcept
{
	return m_edges;
}

std::vector<Face> CGraph::GetFaces() const noexcept
{
	return m_faces;
}

void CGraph::ErschovColoring()
{
	std::unordered_map<int, std::string> vertexColors;
	std::unordered_map<int, int> vertexDegrees;

	for (const auto& edge : m_edges)
	{
		++vertexDegrees[edge.start];
		++vertexDegrees[edge.end];
	}

	std::vector<std::pair<int, int>> sortedVertices(vertexDegrees.begin(), vertexDegrees.end());
	std::sort(sortedVertices.begin(), sortedVertices.end(),
		[](const std::pair<int, int>& a, const std::pair<int, int>& b) {
			return b.second < a.second;
		});

	for (const auto& [vertexId, _] : sortedVertices)
	{
		if (vertexColors.count(vertexId) == 0)
		{
			std::unordered_set<std::string> usedColors;
			for (const auto& edge : m_edges)
			{
				if (edge.start == vertexId && vertexColors.count(edge.end) > 0)
				{
					usedColors.insert(vertexColors[edge.end]);
				}
				else if (edge.end == vertexId && vertexColors.count(edge.start) > 0)
				{
					usedColors.insert(vertexColors[edge.start]);
				}
			}

			std::string color = "Color1";
			while (usedColors.count(color) > 0)
			{
				color = "Color" + std::to_string(std::stoi(color.substr(5)) + 1);
			}

			vertexColors[vertexId] = color;
		}
	}

	m_vertexColors = vertexColors;
}

void CGraph::RenderGraphSFML(const std::string& windowTitle, int width, int height) const
{
	sf::RenderWindow window(sf::VideoMode(width, height), windowTitle);
	window.setFramerateLimit(60);

	const float vertexRadius = 20.0f;

	sf::Color backgroundColor(sf::Color::White);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear(backgroundColor);

		for (const auto& edge : m_edges)
		{
			int startId = edge.start;
			int endId = edge.end;

			if (m_vertices.count(startId) == 0 || m_vertices.count(endId) == 0)
			{
				continue;
			}

			float angle1 = 2 * M_PI * (startId - 1) / m_vertices.size();
			float angle2 = 2 * M_PI * (endId - 1) / m_vertices.size();
			float centerX = width / 2.0f;
			float centerY = height / 2.0f;
			float radius = std::min(width, height) / 3.0f;

			sf::Vector2f startPoint(centerX + radius * std::cos(angle1), centerY + radius * std::sin(angle1));
			sf::Vector2f endPoint(centerX + radius * std::cos(angle2), centerY + radius * std::sin(angle2));

			sf::Vertex line[] = {
				sf::Vertex(startPoint, sf::Color::Black),
				sf::Vertex(endPoint, sf::Color::Black)
			};
			window.draw(line, 2, sf::Lines);
		}

		for (const auto& [id, vertex] : m_vertices)
		{
			float angle = 2 * M_PI * (id - 1) / m_vertices.size();
			float centerX = width / 2.0f;
			float centerY = height / 2.0f;
			float radius = std::min(width, height) / 3.0f;

			sf::Vector2f position(centerX + radius * std::cos(angle), centerY + radius * std::sin(angle));

			sf::CircleShape circle(vertexRadius);
			circle.setPosition(position.x - vertexRadius, position.y - vertexRadius);
			circle.setFillColor(sf::Color::White);
			circle.setOutlineThickness(2.0f);
			circle.setOutlineColor(sf::Color::Black);

			if (m_vertexColors.count(id) > 0)
			{
				std::string colorName = m_vertexColors.at(id);
				if (colorName == "Color1")
					circle.setFillColor(sf::Color::Red);
				else if (colorName == "Color2")
					circle.setFillColor(sf::Color::Green);
				else if (colorName == "Color3")
					circle.setFillColor(sf::Color::Blue);
				else if (colorName == "Color4")
					circle.setFillColor(sf::Color::Yellow);
			}

			window.draw(circle);

			sf::Font font;
			if (!font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-R.ttf"))
			{
				throw std::runtime_error("Failed to load font.");
			}
			sf::Text text(std::to_string(id), font, 14);
			text.setFillColor(sf::Color::Black);
			text.setPosition(position.x - 5, position.y - 5);
			window.draw(text);
		}

		window.display();
	}
}

bool CGraph::CheckFourColorTheorem() const
{
	std::unordered_set<std::string> usedColors;
	for (const auto& [vertex, color] : m_vertexColors)
	{
		usedColors.insert(color);
		if (usedColors.size() > 4)
		{
			return false;
		}
	}
	return true;
}

void CGraph::AddVertex(int id, const std::string& name)
{
	m_vertices.emplace(id, Vertex(id, name));
}

void CGraph::AddEdge(int start, int end)
{
	m_edges.emplace_back(start, end);
}

void CGraph::AddFace(int id, const std::vector<int>& boundaryVertices, const std::string& color)
{
	m_faces.emplace_back(id, boundaryVertices, color);
}