#include "CGraph.h"
#include <gtest/gtest.h>

TEST(GraphColoring, TestSimpleGraph)
{
	std::map<int, std::set<int>> adjacencies = {
		{ 1, { 2, 3, 6 } },
		{ 2, { 1, 4, 5, 7 } },
		{ 3, { 1, 4, 6 } },
		{ 4, { 3, 2, 5, 6 } },
		{ 5, { 4, 2, 6, 7, 9 } },
		{ 6, { 5, 4, 3, 1, 9 } },
		{ 7, { 5, 2, 9 } },
		{ 8, { 9 } },
		{ 9, { 5, 6, 7, 8 } }
	};

	std::vector<std::set<int>> faces = {
		{ 1, 2, 3, 4 },
		{ 1, 2, 3, 6, 7, 9 },
		{ 3, 4, 6 },
		{ 2, 4, 5 },
		{ 2, 5, 7 },
		{ 5, 6, 9 },
		{ 5, 7, 9 },
		{ 4, 5, 6 }
	};

	CGraph graph(adjacencies, faces);

	EXPECT_EQ(graph.GetVertices().size(), 9);
	EXPECT_EQ(graph.GetFaces().size(), 8);
	EXPECT_EQ(graph.GetEdges().size(), 32);
}

TEST(GraphColoring, TestStarGraph)
{
	std::map<int, std::set<int>> adjacencies = {
		{ 1, { 2, 3, 4, 5 } },
		{ 2, { 1 } },
		{ 3, { 1 } },
		{ 4, { 1 } },
		{ 5, { 1 } }
	};

	std::vector<std::set<int>> faces = {
		{ 1, 2, 3 },
		{ 1, 3, 4 },
		{ 1, 4, 5 },
		{ 1, 5, 2 }
	};

	CGraph graph(adjacencies, faces);

	EXPECT_EQ(graph.GetVertices().size(), 5);
	EXPECT_EQ(graph.GetFaces().size(), 4);
	EXPECT_EQ(graph.GetEdges().size(), 8);

	graph.GraphFaceColoring();
	EXPECT_TRUE(graph.CheckFourColorTheorem());

	const auto& vertexColors = graph.GetVertexColors();
	EXPECT_EQ(vertexColors.size(), 5);

	for (const auto& edge : graph.GetEdges())
	{
		EXPECT_NE(vertexColors.at(edge.start), vertexColors.at(edge.end));
	}

	graph.RenderGraphSFML("Graph Visualization", 800, 600);
}

TEST(GraphColoring, TestCompleteGraph)
{
	std::map<int, std::set<int>> adjacencies = {
		{ 1, { 2, 3, 4 } },
		{ 2, { 1, 3, 4 } },
		{ 3, { 1, 2, 4 } },
		{ 4, { 1, 2, 3 } }
	};

	std::vector<std::set<int>> faces = {
		{ 1, 2, 3 },
		{ 1, 3, 4 },
		{ 1, 4, 2 },
		{ 2, 3, 4 }
	};

	CGraph graph(adjacencies, faces);

	EXPECT_EQ(graph.GetVertices().size(), 4);
	EXPECT_EQ(graph.GetFaces().size(), 4);
	EXPECT_EQ(graph.GetEdges().size(), 12);

	graph.GraphFaceColoring();
	EXPECT_TRUE(graph.CheckFourColorTheorem());

	const auto& vertexColors = graph.GetVertexColors();
	EXPECT_EQ(vertexColors.size(), 4);

	for (const auto& edge : graph.GetEdges())
	{
		EXPECT_NE(vertexColors.at(edge.start), vertexColors.at(edge.end));
	}

	graph.RenderGraphSFML("Graph Visualization", 800, 600);
}