#pragma once

#include <vector>

struct Edge
{
	int vertex;
	int flowValue;
	int capacity;
	int reverseEdge;
};

class Graph
{
public:
	Graph() = default;
	explicit Graph(const std::vector<std::vector<Edge>>& adjacencyMatrix);
	~Graph();

	int DinicMaxflow(int s, int t);

private:
	bool BFS(int s, int t);
	int SendFlow(int s, int flow, int t, int ptr[]);

	std::vector<std::vector<Edge>> m_vertices;
	int m_vertexCount;
	int* m_level;
};