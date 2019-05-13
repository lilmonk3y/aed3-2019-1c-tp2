//
// Created by Christian nahuel Rivera on 12/5/19.
//
#include "gtest/gtest.h"
#include "../../src/entity/Graph.h"
#include "../../src/entity/AdjacencyListGraph.h"

struct GraphTest : testing::Test{
    Graph *graph;

    GraphTest(){}

    ~GraphTest(){
        delete graph;
    }
};

TEST_F(GraphTest, whenInstanciatinAGraph_mustDoItAsExpected){
    graph = new AdjacencyListGraph(10);

    ASSERT_EQ(10, graph->getVertex());
}

TEST_F(GraphTest, whenAddingEdges_mustDoItAsExpected){
    graph = new AdjacencyListGraph(10);

    graph->addEdge(2,3, 5);

    ASSERT_TRUE(graph->adjacent(2, 3));
    ASSERT_TRUE(graph->adjacent(3,2));
    ASSERT_FALSE(graph->adjacent(2,1));
}

TEST_F(GraphTest, whenGettingAllEdges_mustNotReturnDuplicated){
    graph = new AdjacencyListGraph(10);
    graph->addEdge(2,3,5);
    graph->addEdge(4,5,6);
    graph->addEdge(7,6,8);

    std::set<Edge> edges = graph->getEdges();

    ASSERT_EQ(3, edges.size());
    ASSERT_TRUE(edges.find(Edge(6,7,8)) != edges.end());
    ASSERT_TRUE(edges.find(Edge(5,4,8)) != edges.end());
    ASSERT_TRUE(edges.find(Edge(3,2,8)) != edges.end());
    ASSERT_FALSE(edges.find(Edge(5,2,8)) == edges.end());
}