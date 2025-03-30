#pragma once

#include <algorithm>
#include <functional>
#include <limits>
#include <list>
#include <stdexcept>
#include <utility>
#include <vector>

using Graph = std::vector<std::vector<int>>;
using GraphLine = std::vector<int>;
using Edges = std::list<std::pair<int, int>>;

class CGraphController
{
public:
	explicit CGraphController()
		: m_graph()
	{
	}
	explicit CGraphController(Graph graph)
		: m_graph(std::move(graph))
	{
	}

	void LoadFromFile(const std::string& filename);
	void ConvertEdgeListToAdjMatrix(const std::vector<std::pair<int, int>>& edgeList);
	[[nodiscard]] std::vector<std::pair<int, int>> ConvertAdjMatrixToEdgeList() const;

	std::pair<int, std::list<int>> FindShortestHamiltonianCycle();

private:
	void HandleMatrix(
		const Graph& matrix,
		const Edges& path,
		int bottomLimit,
		const std::vector<int>& rows,
		const std::vector<int>& columns);
	void CandidateSolution(const Edges& path);
	int GetCost(const Edges& path);
	static void RemoveRowAndColumn(Graph& matrix, int rowIndex, int columnIndex);

	Graph m_graph;
	Edges m_edges;
	int m_cost = std::numeric_limits<int>::max();
};