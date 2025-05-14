#include "Graph.h"
#include <gtest/gtest.h>

Graph BuildGraphFromAdjacencyList(const std::vector<std::vector<Edge>>& adjList)
{
	return Graph(adjList);
}

TEST(DinicMaxFlowTest, SimpleGraphTest)
{
	const int vertexCount = 6;
	std::vector<std::vector<Edge>> adj(vertexCount);

	auto addEdge = [&](int u, int v, int capacity) {
		Edge forward{ v, 0, capacity, static_cast<int>(adj[v].size()) };
		Edge reverse{ u, 0, 0, static_cast<int>(adj[u].size()) };
		adj[u].push_back(forward);
		adj[v].push_back(reverse);
	};

	addEdge(0, 1, 16);
	addEdge(0, 2, 13);
	addEdge(1, 2, 10);
	addEdge(1, 3, 12);
	addEdge(2, 1, 4);
	addEdge(2, 4, 14);
	addEdge(3, 2, 9);
	addEdge(3, 5, 20);
	addEdge(4, 3, 7);
	addEdge(4, 5, 4);

	Graph graph(adj);
	int maxFlow = graph.DinicMaxflow(0, 5);
	EXPECT_EQ(maxFlow, 23);
}

TEST(DinicMaxFlowTest, SourceEqualsSinkTest)
{
	const int vertexCount = 1;
	std::vector<std::vector<Edge>> adj(vertexCount);
	Graph graph(adj);
	int result = graph.DinicMaxflow(0, 0);
	EXPECT_EQ(result, -1);
}

TEST(DinicMaxFlowTest, NoPathTest)
{
	const int vertexCount = 4;
	std::vector<std::vector<Edge>> adj(vertexCount);

	auto addEdge = [&](int u, int v, int capacity) {
		Edge forward{ v, 0, capacity, static_cast<int>(adj[v].size()) };
		Edge reverse{ u, 0, 0, static_cast<int>(adj[u].size()) };
		adj[u].push_back(forward);
		adj[v].push_back(reverse);
	};

	addEdge(0, 1, 10);
	addEdge(2, 3, 5);

	Graph graph(adj);
	int maxFlow = graph.DinicMaxflow(0, 3);
	EXPECT_EQ(maxFlow, 0);
}

TEST(DinicMaxFlowTest, SingleEdgeTest)
{
	const int vertexCount = 2;
	std::vector<std::vector<Edge>> adj(vertexCount);

	auto addEdge = [&](int u, int v, int capacity) {
		Edge forward{ v, 0, capacity, static_cast<int>(adj[v].size()) };
		Edge reverse{ u, 0, 0, static_cast<int>(adj[u].size()) };
		adj[u].push_back(forward);
		adj[v].push_back(reverse);
	};

	addEdge(0, 1, 5);
	Graph graph(adj);
	int maxFlow = graph.DinicMaxflow(0, 1);
	EXPECT_EQ(maxFlow, 5);
}

TEST(DinicMaxFlowTest, MultiplePathsTest)
{
	const int vertexCount = 4;
	std::vector<std::vector<Edge>> adj(vertexCount);

	auto addEdge = [&](int u, int v, int capacity) {
		Edge forward{ v, 0, capacity, static_cast<int>(adj[v].size()) };
		Edge reverse{ u, 0, 0, static_cast<int>(adj[u].size()) };
		adj[u].push_back(forward);
		adj[v].push_back(reverse);
	};

	addEdge(0, 1, 10);
	addEdge(0, 2, 10);
	addEdge(1, 2, 2);
	addEdge(1, 3, 4);
	addEdge(2, 3, 8);
	addEdge(1, 2, 5);

	Graph graph(adj);
	int maxFlow = graph.DinicMaxflow(0, 3);
	EXPECT_EQ(maxFlow, 12);
}

TEST(DinicMaxFlowTest, ComplexGraphTest)
{
	const int vertexCount = 10;
	std::vector<std::vector<Edge>> adj(vertexCount);

	auto addEdge = [&](int u, int v, int capacity) {
		Edge forward{ v, 0, capacity, static_cast<int>(adj[v].size()) };
		Edge reverse{ u, 0, 0, static_cast<int>(adj[u].size()) };
		adj[u].push_back(forward);
		adj[v].push_back(reverse);
	};

	addEdge(0, 1, 16);
	addEdge(0, 2, 13);
	addEdge(0, 3, 10);
	addEdge(1, 4, 12);
	addEdge(2, 4, 14);
	addEdge(2, 5, 4);
	addEdge(3, 4, 9);
	addEdge(3, 5, 7);
	addEdge(4, 9, 20);
	addEdge(5, 6, 10);
	addEdge(6, 9, 15);
	addEdge(6, 7, 4);
	addEdge(7, 9, 5);
	addEdge(8, 9, 20);
	addEdge(9, 9, 10);

	Graph graph = BuildGraphFromAdjacencyList(adj);
	int maxFlow = graph.DinicMaxflow(0, 9);
	EXPECT_EQ(maxFlow, 30);
}

TEST(DinicMaxFlowTest, DiamondGraphTest)
{
    const int vertexCount = 4;
    const int m = 1000000;
    std::vector<std::vector<Edge>> adj(vertexCount);

    auto addEdge = [&](int u, int v, int capacity) {
        Edge forward{ v, 0, capacity, static_cast<int>(adj[v].size()) };
        Edge reverse{ u, 0, 0, static_cast<int>(adj[u].size()) };
        adj[u].push_back(forward);
        adj[v].push_back(reverse);
    };

    addEdge(0, 1, m); 
    addEdge(0, 2, m);
    addEdge(1, 3, m); 
    addEdge(2, 3, m);
    addEdge(2, 1, 1);

    Graph g = BuildGraphFromAdjacencyList(adj);
    int maxFlow = g.DinicMaxflow(0, 3);
    EXPECT_EQ(maxFlow, 2000000);
}