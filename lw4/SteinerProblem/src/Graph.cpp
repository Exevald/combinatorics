#include "Graph.h"
#include <algorithm>
#include <limits>
#include <queue>
#include <unordered_set>

namespace
{
std::vector<int> Dijkstra(int startVertex, int terminalVertex, const std::vector<std::vector<int>>& vertices)
{
	const int INF = -1;
	std::vector<int> distances(vertices.size(), INF);
	std::vector<int> parent(vertices.size(), -1);
	std::vector<bool> visited(vertices.size(), false);

	distances[startVertex] = 0;
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
	pq.push({ 0, startVertex });

	while (!pq.empty())
	{
		auto [d, u] = pq.top();
		pq.pop();

		if (visited[u])
		{
			continue;
		}
		visited[u] = true;

		if (u == terminalVertex)
			break;

		for (int v = 0; v < vertices.size(); ++v)
		{
			if (vertices[u][v] != INF && !visited[v])
			{
				int newDist = distances[u] + vertices[u][v];
				if (distances[v] == INF || newDist < distances[v])
				{
					distances[v] = newDist;
					parent[v] = u;
					pq.push({ newDist, v });
				}
			}
		}
	}

	if (distances[terminalVertex] == INF)
	{
		return {};
	}

	std::vector<int> path;
	int current = terminalVertex;
	while (current != -1)
	{
		path.push_back(current);
		current = parent[current];
	}
	std::reverse(path.begin(), path.end());
	return path;
}
} // namespace

Graph::Graph(const std::vector<std::vector<int>>& adjacencyMatrix)
	: m_vertices(std::move(adjacencyMatrix))
{
}

std::pair<int, std::vector<std::pair<int, int>>> Graph::GetSteinerTree(const std::vector<int>& terminals) const
{
	const int INF = -1;
	std::unordered_set<int> terminalSet(terminals.begin(), terminals.end());
	if (terminals.empty())
	{
		return { INF, {} };
	}

	std::unordered_set<int> steinerTreeVertices;
	std::vector<std::pair<int, int>> steinerTreeEdges;
	int pathLength = 0;

	steinerTreeVertices.insert(terminals[0]);

	while (steinerTreeVertices.size() < terminals.size())
	{
		int minPathLength = INF;
		std::vector<int> bestPath;
		int targetTerminal = -1;

		for (int t : terminals)
		{
			if (steinerTreeVertices.find(t) != steinerTreeVertices.end())
			{
				continue;
			}

			for (int u : steinerTreeVertices)
			{
				auto path = Dijkstra(u, t, m_vertices);
				if (path.empty())
				{
					continue;
				}

				int legnth = 0;
				for (size_t i = 0; i < path.size() - 1; ++i)
				{
					legnth += m_vertices[path[i]][path[i + 1]];
				}

				if (minPathLength == INF || legnth < minPathLength)
				{
					minPathLength = legnth;
					bestPath = path;
					targetTerminal = t;
				}
			}
		}

		if (bestPath.empty() || targetTerminal == -1)
		{
			return { INF, {} };
		}

		for (size_t i = 0; i < bestPath.size() - 1; ++i)
		{
			int u = bestPath[i];
			int v = bestPath[i + 1];
			if (steinerTreeVertices.find(v) == steinerTreeVertices.end())
			{
				steinerTreeVertices.insert(v);
				steinerTreeEdges.emplace_back(u, v);
				pathLength += m_vertices[u][v];
			}
		}
	}

	return { pathLength, steinerTreeEdges };
}