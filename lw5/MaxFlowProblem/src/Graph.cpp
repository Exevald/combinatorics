#include "Graph.h"
#include <algorithm>
#include <cmath>
#include <limits>
#include <list>
#include <queue>
#include <unordered_set>
#include <iostream>

Graph::Graph(const std::vector<std::vector<Edge>>& adjacencyMatrix)
	: m_vertices(adjacencyMatrix)
{
	m_vertexCount = static_cast<int>(m_vertices.size());
	m_level = new int[m_vertexCount];
}

Graph::~Graph()
{
	delete[] m_level;
}

bool Graph::BFS(int s, int t)
{
	for (int i = 0; i < m_vertexCount; i++)
	{
		m_level[i] = -1;
	}

	m_level[s] = 0;

	std::list<int> queue;
	queue.push_back(s);

	std::vector<Edge>::iterator i;
	while (!queue.empty())
	{
		int u = queue.front();
		queue.pop_front();
		for (i = m_vertices[u].begin(); i != m_vertices[u].end(); i++)
		{
			auto& edge = *i;
			if (m_level[edge.vertex] < 0 && edge.flowValue < edge.capacity)
			{
				m_level[edge.vertex] = m_level[u] + 1;

				queue.push_back(edge.vertex);
			}
		}
	}

	return m_level[t] < 0 ? false : true;
}

int Graph::SendFlow(int u, int flow, int t, int start[])
{
	if (u == t)
	{
		return flow;
	}

	for (; start[u] < m_vertices[u].size(); start[u]++)
	{
		auto& edge = m_vertices[u][start[u]];

		if (m_level[edge.vertex] == m_level[u] + 1 && edge.flowValue < edge.capacity)
		{
			int currentFlowValue = std::min(flow, edge.capacity - edge.flowValue);
			int tempFlowValue = SendFlow(edge.vertex, currentFlowValue, t, start);

			if (tempFlowValue > 0)
			{
				edge.flowValue += tempFlowValue;

				m_vertices[edge.vertex][edge.reverseEdge].flowValue -= tempFlowValue;
				return tempFlowValue;
			}
		}
	}

	return 0;
}

int Graph::DinicMaxflow(int s, int t)
{
	if (s == t)
	{
		return -1;
	}

	int totalFlowValue = 0;

	while (BFS(s, t) == true)
	{
		int* start = new int[m_vertexCount + 1]{ 0 };
		while (int flow = SendFlow(s, __INT_MAX__, t, start))
		{
			totalFlowValue += flow;
		}

		delete[] start;
	}

	return totalFlowValue;
}