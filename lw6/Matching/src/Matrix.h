#pragma once

#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

using AdjacencyMatrix = std::vector<std::vector<double>>;
using Edges = std::vector<std::pair<int, int>>;
constexpr int INF = std::numeric_limits<int>::max();

class Matrix
{
public:
	void ReadGraphFromFile(const std::string& filename);
	AdjacencyMatrix GetAdjacencyMatrix();
	static Edges AdjacencyMatrixToEdges(const AdjacencyMatrix& matrix);
	static bool GetInvertedMatrix(const AdjacencyMatrix& matrix, AdjacencyMatrix& invertedMatrix);

	static constexpr int NO_EDGE = std::numeric_limits<int>::max();

private:
	void AddEdge(int u, int v, int w);

	AdjacencyMatrix m_adjacencyMatrix;
};
