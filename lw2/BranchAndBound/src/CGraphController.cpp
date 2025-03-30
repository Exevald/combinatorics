#include "CGraphController.h"
#include <fstream>
#include <numeric>
#include <ranges>

namespace
{
const int m_removed = std::numeric_limits<int>::max() - 1;

bool IsAdjMatrixValid(const Graph& matrix)
{
	if (matrix.empty())
	{
		return false;
	}

	size_t size = matrix.size();

	if (!std::ranges::all_of(matrix, [size](const auto& row) {
			return row.size() == size;
		}))
	{
		return false;
	}

	return std::ranges::all_of(matrix, [](const auto& row) {
		return std::ranges::all_of(row, [](int value) {
			return value >= 0;
		});
	});
}

bool IsSquareMatrix(const Graph& matrix)
{
	if (matrix.empty())
	{
		return false;
	}
	size_t size = matrix.size();
	return std::ranges::all_of(matrix, [size](const auto& row) {
		return row.size() == size;
	});
}

bool IsEdgeListValid(const std::vector<std::pair<int, int>>& edgeList)
{
	return std::ranges::all_of(edgeList, [](const auto& edge) {
		return edge.first >= 0 && edge.second >= 0;
	});
}

int GetRealRowIndex(const std::vector<int>& rows, int rowIndex)
{
	if (rowIndex < 0 || rowIndex >= rows.size())
	{
		throw std::out_of_range("Invalid row index");
	}
	return rows[rowIndex];
}

int GetRealColumnIndex(const std::vector<int>& columns, int columnIndex)
{
	if (columnIndex < 0 || columnIndex >= columns.size())
	{
		throw std::out_of_range("Invalid column index");
	}
	return columns[columnIndex];
}

int GetPenalty(const Graph& matrix, int rowIndex, int columnIndex)
{
	int rowPenalty, columnPenalty;
	rowPenalty = columnPenalty = std::numeric_limits<int>::max();
	for (size_t i = 0; i < matrix.size(); ++i)
	{
		if (i != rowIndex)
		{
			rowPenalty = std::min(rowPenalty, matrix[i][columnIndex]);
		}
		if (i != columnIndex)
		{
			columnPenalty = std::min(columnPenalty, matrix[rowIndex][i]);
		}
	}
	if (rowPenalty > std::numeric_limits<int>::max() - columnPenalty)
	{
		return std::numeric_limits<int>::max();
	}
	return rowPenalty + columnPenalty;
}

int SubtractFromMatrix(Graph& matrix)
{
	std::vector<int> minRow(matrix.size(), std::numeric_limits<int>::max());
	std::vector<int> minColumn(matrix.size(), std::numeric_limits<int>::max());

	for (size_t i = 0; i < matrix.size(); ++i)
	{
		for (size_t j = 0; j < matrix.size(); ++j)
		{
			if (matrix[i][j] != std::numeric_limits<int>::max() && matrix[i][j] < minRow[i])
			{
				minRow[i] = matrix[i][j];
			}
		}

		for (size_t j = 0; j < matrix.size(); ++j)
		{
			if (matrix[i][j] != std::numeric_limits<int>::max())
			{
				matrix[i][j] -= minRow[i];
			}
		}
	}

	for (size_t j = 0; j < matrix.size(); ++j)
	{
		for (auto& i : matrix)
		{
			if (i[j] != std::numeric_limits<int>::max() && i[j] < minColumn[j])
			{
				minColumn[j] = i[j];
			}
		}

		for (auto& i : matrix)
		{
			if (i[j] != std::numeric_limits<int>::max())
			{
				i[j] -= minColumn[j];
			}
		}
	}

	return std::reduce(minColumn.begin(), minColumn.end(),
		std::reduce(minRow.begin(), minRow.end(), 0));
}

std::list<std::pair<int, int>> FindBestZeros(const Graph& matrix)
{
	std::list<std::pair<int, int>> zeros;
	std::list<int> coeffList;

	int maxCoeff = 0;
	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = 0; j < matrix.size(); ++j)
		{
			if (matrix[i][j] == 0 && i != j)
			{
				zeros.emplace_back(i, j);
				coeffList.push_back(GetPenalty(matrix, i, j));
				maxCoeff = std::max(maxCoeff, coeffList.back());
			}
		}
	}

	auto zIter = zeros.begin();
	auto cIter = coeffList.begin();
	while (zIter != zeros.end())
	{
		if (*cIter != maxCoeff)
		{
			zIter = zeros.erase(zIter);
			cIter = coeffList.erase(cIter);
		}
		else
		{
			++zIter;
			++cIter;
		}
	}

	return zeros;
}

void AddInfinityToMatrix(Graph& matrix)
{
	std::vector<bool> infinityRow(matrix.size(), false);
	std::vector<bool> infinityColumn(matrix.size(), false);

	for (size_t i = 0; i < matrix.size(); i++)
	{
		for (size_t j = 0; j < matrix.size(); j++)
		{

			if (matrix[i][j] == m_removed)
			{
				infinityRow[i] = true;
				infinityColumn[j] = true;
			}
		}
	}

	size_t notInf = 0;
	for (size_t i = 0; i < infinityRow.size(); i++)
	{
		if (!infinityRow[i])
		{
			notInf = i;
			break;
		}
	}

	for (size_t j = 0; j < infinityColumn.size(); j++)
	{
		if (!infinityColumn[j])
		{
			matrix[notInf][j] = m_removed;
			break;
		}
	}
}

} // namespace

void CGraphController::LoadFromFile(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
	{
		throw std::runtime_error("Failed to open file for reading");
	}

	m_graph.clear();

	int numEdges;
	file >> numEdges;

	std::vector<std::pair<int, int>> edgeList;
	edgeList.reserve(numEdges);

	for (int i = 0; i < numEdges; ++i)
	{
		int from, to;
		file >> from >> to;
		edgeList.emplace_back(from, to);
	}

	ConvertEdgeListToAdjMatrix(edgeList);
}

void CGraphController::ConvertEdgeListToAdjMatrix(const std::vector<std::pair<int, int>>& edgeList)
{
	if (!IsEdgeListValid(edgeList))
	{
		throw std::runtime_error("Edge list is invalid");
	}

	int maxVertex = 0;
	for (const auto& edge : edgeList)
	{
		maxVertex = std::max(maxVertex, std::max(edge.first, edge.second));
	}

	m_graph.clear();
	m_graph.resize(maxVertex + 1, GraphLine(maxVertex + 1, 0));

	for (const auto& edge : edgeList)
	{
		m_graph[edge.first][edge.second] = 1;
	}
}

std::vector<std::pair<int, int>> CGraphController::ConvertAdjMatrixToEdgeList() const
{
	if (!IsAdjMatrixValid(m_graph))
	{
		throw std::runtime_error("Adjacency matrix is invalid");
	}

	std::vector<std::pair<int, int>> edgeList;
	for (size_t i = 0; i < m_graph.size(); ++i)
	{
		for (size_t j = 0; j < m_graph[i].size(); ++j)
		{
			if (m_graph[i][j] == 1)
			{
				edgeList.emplace_back(i, j);
			}
		}
	}

	return edgeList;
}

std::pair<int, std::list<int>> CGraphController::FindShortestHamiltonianCycle()
{
	for (size_t i = 0; i < m_graph.size(); i++)
	{
		m_graph[i][i] = m_removed;
	}

	std::vector<int> rows(m_graph.size());
	std::vector<int> columns(m_graph.size());
	std::iota(rows.begin(), rows.end(), 0);
	std::iota(columns.begin(), columns.end(), 0);

	HandleMatrix(m_graph, m_edges, 0, rows, columns);

	std::list<int> solution;
	solution.push_back(0);
	while (!m_edges.empty())
	{
		auto it = m_edges.begin();
		while (it != m_edges.end())
		{
			if (it->first == solution.back())
			{
				solution.push_back(it->second);
				it = m_edges.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	return { m_cost, solution };
}

void CGraphController::HandleMatrix(
	const Graph& matrix,
	const Edges& path,
	int bottomLimit,
	const std::vector<int>& rows,
	const std::vector<int>& columns)
{
	auto size = matrix.size();
	if (size < 2)
	{
		throw std::logic_error("Matrix smaller than 2x2");
	}

	if (size == 2)
	{
		int item = matrix[0][0];
		int i = (item == m_removed || item == std::numeric_limits<int>::max()) ? 1 : 0;
		Edges result(path);
		result.emplace_back(GetRealRowIndex(rows, 0), GetRealColumnIndex(columns, i));
		result.emplace_back(GetRealRowIndex(rows, 1), GetRealColumnIndex(columns, 1 - i));
		CandidateSolution(result);
		return;
	}

	Graph editedMatrix(matrix);
	bottomLimit += SubtractFromMatrix(editedMatrix);
	if (bottomLimit > m_cost)
	{
		return;
	}

	auto zeros = FindBestZeros(editedMatrix);
	if (zeros.empty())
	{
		return;
	}

	auto edge = zeros.front();
	std::vector<int> newRows = rows;
	std::vector<int> newColumns = columns;

	newRows.erase(newRows.begin() + edge.first);
	newColumns.erase(newColumns.begin() + edge.second);

	Graph newMatrix(editedMatrix);
	RemoveRowAndColumn(newMatrix, edge.first, edge.second);

	auto newPath(path);
	newPath.emplace_back(GetRealRowIndex(rows, edge.first), GetRealColumnIndex(columns, edge.second));
	AddInfinityToMatrix(newMatrix);
	HandleMatrix(newMatrix, newPath, bottomLimit, newRows, newColumns);

	newMatrix = editedMatrix;
	newMatrix[edge.first][edge.second] = std::numeric_limits<int>::max();
	HandleMatrix(newMatrix, path, bottomLimit, rows, columns);
}

void CGraphController::CandidateSolution(const Edges& path)
{
	int curCost;
	if (m_cost <= (curCost = GetCost(path)))
	{
		return;
	}
	m_cost = curCost;
	m_edges = path;
}

int CGraphController::GetCost(const Edges& path)
{
	int result = 0;
	for (auto& item : path)
	{
		auto el = m_graph[item.first][item.second];
		if (el == std::numeric_limits<int>::max() || item.first == item.second)
		{
			return std::numeric_limits<int>::max();
		}
		result += el;
	}

	return result;
}

void CGraphController::RemoveRowAndColumn(Graph& matrix, int rowIndex, int columnIndex)
{
	if (rowIndex >= matrix.size() || columnIndex >= matrix.size())
	{
		throw std::out_of_range("Invalid rowIndex or columnIndex index");
	}

	matrix.erase(matrix.begin() + rowIndex);
	for (auto& row : matrix)
	{
		row.erase(row.begin() + columnIndex);
	}
}
