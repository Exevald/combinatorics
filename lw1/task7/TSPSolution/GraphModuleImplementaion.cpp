#include "CGraph.h"
#include <iostream>
#include <string>
#include <algorithm>

Graph CGraph::ReadMatrix(std::ifstream& inFile)
{
	Graph graph;
	std::string line;
	int linePos = 0;

	while (std::getline(inFile, line))
	{
		GraphLine levelLine;
		for (int i = 0; i < line.length(); i++)
		{
			levelLine.push_back(line[i]);
		}

		graph.push_back(levelLine);
	}

	return graph;
}

std::pair<int, std::vector<GraphType>> CGraph::GetShortestPath(const Graph& graph) 
{
	int numVertices = graph.size();
	std::vector<GraphType> vertices(numVertices);

	for (int i = 0; i < numVertices; ++i) 
	{
		vertices[i] = i;
	}

	std::vector<GraphType> shortestPath;
	int minLength = std::numeric_limits<int>::max();

	do {
		int currentLength = 0;

		for (size_t i = 0; i < vertices.size() - 1; ++i)
		{
			int from = vertices[i];
			int to = vertices[i + 1];

			currentLength += graph[from][to];
		}

		if (currentLength < minLength)
		{
			minLength = currentLength;
			shortestPath = vertices;
		}

	} while (std::next_permutation(vertices.begin() + 1, vertices.end()));

	return { minLength, shortestPath };
}