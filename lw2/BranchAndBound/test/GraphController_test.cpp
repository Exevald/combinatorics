#include "CGraphController.h"
#include <gtest/gtest.h>
#include <sstream>

CGraphController LoadMatrixFromString(const std::string& matrixString)
{
	std::stringstream ss(matrixString);
	int size;
	ss >> size;

	Graph adjacencyMatrix(size, GraphLine(size, 0));
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			std::string value;
			ss >> value;

			if (value == "INF")
			{
				adjacencyMatrix[i][j] = std::numeric_limits<int>::max();
			}
			else
			{
				adjacencyMatrix[i][j] = std::stoi(value);
			}
		}
	}

	return CGraphController(adjacencyMatrix);
}

TEST(CGraphTest, SimpleGraph)
{
	std::string matrixString = R"(
        4
        INF 10 15 20
        10 INF 35 25
        15 35 INF 30
        20 25 30 INF
    )";
	auto graph = LoadMatrixFromString(matrixString);

	auto [cost, path] = graph.FindShortestHamiltonianCycle();
	EXPECT_EQ(cost, 80);
	EXPECT_EQ(path.size(), 5);
}

TEST(CGraphTest, SmallGraph)
{
	std::string matrixString = R"(
        2
        INF 1
        1 INF
    )";
	auto graph = LoadMatrixFromString(matrixString);

	auto [cost, path] = graph.FindShortestHamiltonianCycle();
	EXPECT_EQ(cost, 2);
	EXPECT_EQ(path.size(), 3);
}

TEST(CGraphTest, LargeGraph)
{
	std::string matrixString = R"(
        5
        INF 1 1 1 1
        1 INF 1 1 1
        1 1 INF 1 1
        1 1 1 INF 1
        1 1 1 1 INF
    )";
	auto graph = LoadMatrixFromString(matrixString);

	auto [cost, path] = graph.FindShortestHamiltonianCycle();
	EXPECT_EQ(cost, 5);
	EXPECT_EQ(path.size(), 6);
}

TEST(CGraphTest, PerformanceTest)
{
	std::string matrixString = R"(
        10
        INF 1 2 3 4 5 6 7 8 9
        1 INF 1 2 3 4 5 6 7 8
        2 1 INF 1 2 3 4 5 6 7
        3 2 1 INF 1 2 3 4 5 6
        4 3 2 1 INF 1 2 3 4 5
        5 4 3 2 1 INF 1 2 3 4
        6 5 4 3 2 1 INF 1 2 3
        7 6 5 4 3 2 1 INF 1 2
        8 7 6 5 4 3 2 1 INF 1
        9 8 7 6 5 4 3 2 1 INF
    )";
	auto graph = LoadMatrixFromString(matrixString);

	auto [cost, path] = graph.FindShortestHamiltonianCycle();
	EXPECT_EQ(cost, 18);
	EXPECT_EQ(path.size(), 11);
}