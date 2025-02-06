#pragma once

#include <vector>
#include <fstream>

typedef int GraphType;
typedef std::vector<GraphType> GraphLine;
typedef std::vector<GraphLine> Graph;

class CGraph
{
public:
	static Graph ReadMatrix(std::ifstream& inFile);
	static std::pair<int, std::vector<GraphType>> GetShortestPath(const Graph& graph);
private:
};