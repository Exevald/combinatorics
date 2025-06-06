#include "Matrix.h"

#include <random>

namespace
{
void GetExtendedMatrix(const AdjacencyMatrix& matrix, AdjacencyMatrix& extendedMatrix)
{
	const auto rows = matrix.size();
	for (auto i = 0; i < rows; ++i)
	{
		std::copy(matrix[i].begin(), matrix[i].end(), extendedMatrix[i].begin());
		extendedMatrix[i][rows + i] = 1.0;
	}
}

void GetRowWithMaxElement(
	const size_t& currentRow,
	const AdjacencyMatrix& extendedMatrix,
	size_t& rowWithMaxElement)
{
	for (auto j = currentRow; j < extendedMatrix.size(); ++j)
	{
		if (std::fabs(extendedMatrix[j][currentRow])
			> std::fabs(extendedMatrix[rowWithMaxElement][currentRow]))
		{
			rowWithMaxElement = j;
		}
	}
}

void SwapRows(const size_t& rowWithMaxElement, const size_t& currentRow, AdjacencyMatrix& extendedMatrix)
{
	if (rowWithMaxElement != currentRow)
	{
		std::swap(extendedMatrix[currentRow], extendedMatrix[rowWithMaxElement]);
	}
}

void DivideRow(AdjacencyMatrix& extendedMatrix, const size_t& currentRow)
{
	const double dividedRow = extendedMatrix[currentRow][currentRow];
	for (auto j = 0; j < extendedMatrix.size() * 2; ++j)
	{
		extendedMatrix[currentRow][j] /= dividedRow;
	}
}

void ResetRowsToZero(AdjacencyMatrix& extendedMatrix, const size_t& currentRow)
{
	for (auto j = 0; j < extendedMatrix.size(); ++j)
	{
		if (j != currentRow)
		{
			const double factor = extendedMatrix[j][currentRow];
			for (auto k = 0; k < extendedMatrix.size() * 2; ++k)
			{
				extendedMatrix[j][k] -= factor * extendedMatrix[currentRow][k];
			}
		}
	}
}

void ExtractInvertedMatrix(AdjacencyMatrix& invertedMatrix, const AdjacencyMatrix& extendedMatrix)
{
	invertedMatrix.resize(extendedMatrix.size());
	for (auto i = 0; i < extendedMatrix.size(); ++i)
	{
		invertedMatrix[i].resize(extendedMatrix[i].size());
		for (auto j = 0; j < extendedMatrix.size(); ++j)
		{
			invertedMatrix[i][j] = extendedMatrix[i][j + extendedMatrix.size()];
		}
	}
}
} // namespace

void Matrix::ReadGraphFromFile(const std::string& filename)
{
	std::ifstream inputFile(filename);
	if (!inputFile.is_open())
	{
		throw std::invalid_argument("File could not be opened");
	}

	m_adjacencyMatrix.clear();
	if (inputFile.peek() == std::ifstream::traits_type::eof())
	{
		return;
	}

	int numVertices, edgeCount;
	inputFile >> numVertices >> edgeCount;

	m_adjacencyMatrix.resize(numVertices, std::vector(numVertices, static_cast<double>(INF)));

	int u, v, w;
	for (auto i = 0; i < edgeCount; ++i)
	{
		inputFile >> u >> v >> w;
		AddEdge(u, v, w);
	}
}

bool Matrix::GetInvertedMatrix(const AdjacencyMatrix& matrix, AdjacencyMatrix& invertedMatrix)
{
	const auto rows = matrix.size();

	AdjacencyMatrix extendedMatrix(rows, std::vector(rows * 2, 0.0));
	GetExtendedMatrix(matrix, extendedMatrix);

	for (auto i = 0; i < rows; ++i)
	{
		size_t rowWithMaxElement = i;
		GetRowWithMaxElement(i, extendedMatrix, rowWithMaxElement);

		if (std::fabs(extendedMatrix[rowWithMaxElement][i]) < 1e-10)
		{
			return false;
		}

		SwapRows(rowWithMaxElement, i, extendedMatrix);
		DivideRow(extendedMatrix, i);
		ResetRowsToZero(extendedMatrix, i);
	}

	ExtractInvertedMatrix(invertedMatrix, extendedMatrix);

	return true;
}

AdjacencyMatrix Matrix::GetAdjacencyMatrix()
{
	return m_adjacencyMatrix;
}

Edges Matrix::AdjacencyMatrixToEdges(const AdjacencyMatrix& matrix)
{
	Edges edges;
	const int vertexesCount = static_cast<int>(matrix.size());
	for (auto i = 0; i < vertexesCount; i++)
	{
		for (auto j = 0; j < vertexesCount; j++)
		{
			if (matrix[i][j] != NO_EDGE)
			{
				edges.emplace_back(i, j);
			}
		}
	}
	return edges;
}

void Matrix::AddEdge(const int u, const int v, const int w)
{
	m_adjacencyMatrix[u][v] = w;
}