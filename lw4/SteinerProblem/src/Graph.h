#pragma once

#include <vector>

class Graph
{
public:
	Graph() = default;
	explicit Graph(const std::vector<std::vector<int>>& adjacencyMatrix);

	std::pair<int, std::vector<std::pair<int, int>>> GetSteinerTree(const std::vector<int>& terminals) const;

private:
	std::vector<std::vector<int>> m_vertices;
};