#pragma once

#include "Matrix.h"

class MaxMatchingSolver
{
public:
	explicit MaxMatchingSolver(Matrix matrix);

	Edges FindMaximumMatching();
	static void FindMatching(
		size_t vertices,
		const Edges& edges,
		AdjacencyMatrix& tutteMatrix,
		std::vector<bool>& used,
		Edges& matchedEdges);

private:
	Matrix m_matrix;
};