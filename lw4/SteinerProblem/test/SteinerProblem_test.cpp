#include "Graph.h"
#include <gtest/gtest.h>

TEST(SteinerProblem, TestLinearGraph)
{
	std::vector<std::vector<int>> adjMatrix = {
		{ 0, 1, -1, -1 },
		{ 1, 0, 2, -1 },
		{ -1, 2, 0, 3 },
		{ -1, -1, 3, 0 }
	};

	Graph graph(adjMatrix);
	std::vector<int> terminals = { 0, 3 };

	auto [pathLength, steinerTreeEdges] = graph.GetSteinerTree(terminals);

	EXPECT_EQ(pathLength, 6);
	EXPECT_EQ(steinerTreeEdges.size(), 3);
	EXPECT_TRUE((steinerTreeEdges[0] == std::make_pair(0, 1) || steinerTreeEdges[0] == std::make_pair(1, 0)));
	EXPECT_TRUE((steinerTreeEdges[1] == std::make_pair(1, 2) || steinerTreeEdges[1] == std::make_pair(2, 1)));
	EXPECT_TRUE((steinerTreeEdges[2] == std::make_pair(2, 3) || steinerTreeEdges[2] == std::make_pair(3, 2)));
}

TEST(SteinerProblem, TestIsolatedTerminals)
{
	std::vector<std::vector<int>> adjacencyMatrix = {
		{ 0, 1, -1, -1, -1, -1 },
		{ 1, 0, 2, -1, -1, -1 },
		{ -1, 2, 0, -1, -1, -1 },
		{ -1, -1, -1, 0, -1, -1 },
		{ -1, -1, -1, -1, 0, -1 },
		{ -1, -1, -1, -1, -1, 0 }
	};

	Graph graph(adjacencyMatrix);
	std::vector<int> terminals = { 0, 3, 4, 5 };

	auto [pathLength, steinerTreeEdges] = graph.GetSteinerTree(terminals);

	EXPECT_EQ(pathLength, -1);
	EXPECT_TRUE(steinerTreeEdges.empty());
}

TEST(SteinerProblem, TestTwoPaths)
{
	std::vector<std::vector<int>> adjMatrix = {
		{ 0, 5, 1, -1 },
		{ 5, 0, 2, 1 },
		{ 1, 2, 0, 4 },
		{ -1, 1, 4, 0 }
	};
	Graph graph(adjMatrix);
	std::vector<int> terminals = { 0, 3 };

	auto [pathLength, steinerTreeEdges] = graph.GetSteinerTree(terminals);

	EXPECT_EQ(pathLength, 4);
	EXPECT_EQ(steinerTreeEdges.size(), 3);
	EXPECT_TRUE((steinerTreeEdges[0] == std::make_pair(0, 2) || steinerTreeEdges[0] == std::make_pair(2, 0)));
	EXPECT_TRUE((steinerTreeEdges[1] == std::make_pair(1, 2) || steinerTreeEdges[1] == std::make_pair(2, 1)));
	EXPECT_TRUE((steinerTreeEdges[2] == std::make_pair(1, 3) || steinerTreeEdges[2] == std::make_pair(3, 1)));
}

TEST(SteinerProblem, TestDisconnectedComponents)
{
	std::vector<std::vector<int>> adjMatrix = {
		{ 0, 1, -1, -1 },
		{ 1, 0, -1, -1 },
		{ -1, -1, 0, 1 },
		{ -1, -1, 1, 0 }
	};
	Graph graph(adjMatrix);
	std::vector<int> terminals = { 0, 2 };

	auto [pathLength, steinerTreeEdges] = graph.GetSteinerTree(terminals);

	EXPECT_EQ(pathLength, -1);
	EXPECT_TRUE(steinerTreeEdges.empty());
}