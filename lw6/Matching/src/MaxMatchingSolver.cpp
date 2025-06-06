#include "MaxMatchingSolver.h"

#include <random>
#include <utility>

namespace
{
double GetRandomDouble()
{
	std::mt19937_64 rng{ std::random_device{}() };
	std::uniform_real_distribution dist{ 1.0, 2.0 };
	return dist(rng);
}

AdjacencyMatrix GetTutteMatrix(const AdjacencyMatrix& matrix)
{
	const size_t vertices = matrix.size();
	AdjacencyMatrix tutteMatrix(vertices, std::vector<double>(vertices));

	for (size_t i = 0; i < vertices; ++i)
	{
		for (size_t j = 0; j < vertices; ++j)
		{
			if (matrix[i][j] == Matrix::NO_EDGE && !static_cast<bool>(tutteMatrix[i][j]))
			{
				tutteMatrix[i][j] = 0;
			}
			else
			{
				tutteMatrix[j][i] = GetRandomDouble();
				tutteMatrix[i][j] = -tutteMatrix[j][i];
			}
		}
	}

	return tutteMatrix;
}
} // namespace

MaxMatchingSolver::MaxMatchingSolver(Matrix matrix)
	: m_matrix(std::move(matrix))
{
}

Edges MaxMatchingSolver::FindMaximumMatching()
{
	if (m_matrix.GetAdjacencyMatrix().empty())
	{
		return {};
	}

	constexpr int MAX_ATTEMPTS = 100;
	Edges bestMatching;
	const auto& originalEdges = Matrix::AdjacencyMatrixToEdges(m_matrix.GetAdjacencyMatrix());

	for (int attempt = 0; attempt < MAX_ATTEMPTS; ++attempt)
	{
		AdjacencyMatrix tutteMatrix = GetTutteMatrix(m_matrix.GetAdjacencyMatrix());
		std::vector used(tutteMatrix.size(), false);
		Edges currentMatching;

		FindMatching(tutteMatrix.size(), originalEdges, tutteMatrix, used, currentMatching);

		if (currentMatching.size() > bestMatching.size())
		{
			bestMatching = std::move(currentMatching);
			if (bestMatching.size() * 2 == tutteMatrix.size())
			{
				break;
			}
		}
	}

	return bestMatching;
}

void MaxMatchingSolver::FindMatching(
	const size_t vertices,
	const Edges& edges,
	AdjacencyMatrix& tutteMatrix,
	std::vector<bool>& used,
	Edges& matchedEdges)
{
	int unusedVertices = 0;
	for (const bool usedVertex : used)
	{
		if (!usedVertex)
		{
			unusedVertices++;
		}
	}
	if (unusedVertices < 2)
	{
		return;
	}

	AdjacencyMatrix invertedMatrix(vertices, std::vector<double>(vertices));
	if (!Matrix::GetInvertedMatrix(tutteMatrix, invertedMatrix))
	{
		return;
	}

	for (auto [u, v] : edges)
	{
		if (used[u] || used[v])
		{
			continue;
		}

		if (invertedMatrix[v][u] != 0)
		{
			matchedEdges.emplace_back(u, v);
			used[u] = true;
			used[v] = true;
			for (size_t i = 0; i < vertices; i++)
			{
				tutteMatrix[u][i] = 0;
				tutteMatrix[v][i] = 0;
				tutteMatrix[i][u] = 0;
				tutteMatrix[i][v] = 0;
			}
			FindMatching(vertices, edges, tutteMatrix, used, matchedEdges);
		}
	}
}