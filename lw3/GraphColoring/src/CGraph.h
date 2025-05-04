#pragma once

#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

struct Vertex
{
	int id = 0;
	std::string name;

	Vertex() = default;

	explicit Vertex(int id, std::string name = "")
		: id(id)
		, name(std::move(name))
	{
	}
};

struct Edge
{
	int start;
	int end;

	explicit Edge(int start, int end)
		: start(start)
		, end(end)
	{
	}
};

struct Face
{
	int id;
	std::vector<int> boundaryVertices;
	std::string color;

	explicit Face(int id, const std::vector<int>& boundaryVertices, std::string color = "")
		: id(id)
		, boundaryVertices(boundaryVertices)
		, color(std::move(color))
	{
	}
};

class CGraph
{
public:
	CGraph() = default;

	explicit CGraph(const std::map<int, std::set<int>>& adjacencies, const std::vector<std::set<int>>& faces);
	explicit CGraph(const std::vector<std::vector<int>>& adjacencyMatrix);

	[[nodiscard]] std::unordered_map<int, Vertex> GetVertices() const noexcept;
	[[nodiscard]] std::vector<Edge> GetEdges() const noexcept;
	[[nodiscard]] std::vector<Face> GetFaces() const noexcept;

	void ErschovColoring();
	void GraphFaceColoring();
	bool CheckFourColorTheorem() const;

	[[nodiscard]] const std::unordered_map<int, std::string>& GetVertexColors() const noexcept
	{
		return m_vertexColors;
	};

	void RenderGraphSFML(const std::string& windowTitle, int width, int height) const;

	~CGraph() = default;

private:
	void AddVertex(int id, const std::string& name = "");
	void AddEdge(int start, int end);
	void AddFace(int id, const std::vector<int>& boundaryVertices, const std::string& color = "");
	CGraph CreateDualGraph() const;
	bool IsBipartite() const;
	void FillBipartiteGraph();
	void ConvertDualGraphToDefault(std::unordered_map<int, std::string> dualColors);

	std::unordered_map<int, Vertex> m_vertices;
	std::vector<Edge> m_edges;
	std::vector<Face> m_faces;

	std::unordered_map<int, std::string> m_vertexColors;
};