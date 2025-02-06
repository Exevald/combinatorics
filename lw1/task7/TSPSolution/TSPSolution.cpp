#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include "CGraph.h"

void TimeCount(int initialCount, double duration, std::ofstream& output)
{
	long double dur = duration;
	for (int i = initialCount + 1; i <= 15; i++)
	{
		dur *= i;
	}
	dur /= 3600;
	output << "N = 15: " << dur << " hours" << std::endl;

	for (int i = 16; i <= 20; i++)
	{
		dur *= i;
	}
	dur /= 24;
	output << "N = 20: " << dur << " days" << std::endl;

	for (int i = 21; i <= 50; i++)
	{
		dur *= i;
	}
	dur /= 365;
	output << "N = 50: " << dur << " years" << std::endl;

	for (int i = 51; i <= 100; i++)
	{
		dur *= i;
	}
	output << "N = 100: " << dur << " years" << std::endl;
}

int main()
{
	auto start = std::chrono::steady_clock::now();
	std::ifstream inputFile;
	std::ofstream outputFile;

	inputFile.open("input.txt");
	outputFile.open("output.txt");

	if (!inputFile.is_open())
	{
		std::cout << "Error of opening input file" << std::endl;
		return EXIT_FAILURE;
	}
	if (!outputFile.is_open())
	{
		std::cout << "Error of opening output file" << std::endl;
		return EXIT_FAILURE;
	}

	auto graph = CGraph::ReadMatrix(inputFile);
	const auto shortestPathInfo = CGraph::GetShortestPath(graph);
	outputFile << shortestPathInfo.first << std::endl;

	for (const auto pathItem : shortestPathInfo.second)
	{
		outputFile << pathItem << "->";
	}
	outputFile << shortestPathInfo.second[0] << " " << std::endl << std::endl;

	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed = end - start;
	outputFile << "Time: " << elapsed.count() << std::endl;

	TimeCount(graph.size(), elapsed.count(), outputFile);

	return EXIT_SUCCESS;
}