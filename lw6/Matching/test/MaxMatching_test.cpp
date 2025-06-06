#include "MaxMatchingSolver.h"
#include <gtest/gtest.h>

void FindMaxMatchingTest(const std::string& filename, const Edges& expectedPairs)
{
	Matrix graph;
	graph.ReadGraphFromFile(filename);

	MaxMatchingSolver FindMaxMatching(graph);
	const auto maxMatching = FindMaxMatching.FindMaximumMatching();

	EXPECT_EQ(expectedPairs, maxMatching);
}

TEST(FindMaxMatching, TestEmptyGraph)
{
	FindMaxMatchingTest("emptyGraph.txt", {});
}

TEST(FindMaxMatching, TestOrdinaryGraph)
{
	FindMaxMatchingTest("ordinaryGraph.txt", { { 0, 2 }, { 1, 3 } });
}

TEST(FindMaxMatching, TestFullGraph)
{
	FindMaxMatchingTest("fullGraph.txt", { { 0, 1 }, { 2, 5 }, { 4, 3 } });
}

TEST(FindMaxMatching, TestLineGraph)
{
	FindMaxMatchingTest("lineGraph.txt", { { 0, 1 }, { 2, 3 } });
}

TEST(FindMaxMatching, TestCycleGraph)
{
	FindMaxMatchingTest("cycleGraph.txt", { { 0, 1 }, { 2, 3 } });
}

TEST(FindMaxMatching, TestBipartiteGraph)
{
	FindMaxMatchingTest("bipartiteGraph.txt", { { 0, 3 }, { 1, 4 }, { 2, 5 } });
}