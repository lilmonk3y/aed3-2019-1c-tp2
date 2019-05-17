//
// Created by Christian nahuel Rivera on 12/5/19.
//
#include "gtest/gtest.h"
#include "../../src/entity/core/Graph.h"
#include "../../src/entity/core/AdjacencyListGraph.h"
#include "../../src/entity/core/DirectedTreeGraph.h"

struct GraphTest : testing::Test{
    Graph *graph;

    GraphTest(){
        //graph = new AdjacencyListGraph(1);
        graph = new DirectedTreeGraph(1);
    }

    ~GraphTest(){
        delete graph;
    }
};

TEST_F(GraphTest, whenInstanciatinAGraph_mustDoItAsExpected){
    graph->resetSize(10);

    ASSERT_EQ(10, graph->getVertex());
}

// Only for non directed graphs
TEST_F(GraphTest, whenAddingEdges_mustDoItAsExpected){
    if(typeid(graph) == typeid(AdjacencyListGraph)) {
        graph->resetSize(10);

        graph->addEdge(2, 3, 5);

        ASSERT_TRUE(graph->adjacent(2, 3));
        ASSERT_TRUE(graph->adjacent(3, 2));
        ASSERT_FALSE(graph->adjacent(2, 1));
    }
}

TEST_F(GraphTest,whenAddingEdges_mustDoItAsExpected2){
    graph->resetSize(4);
    
    graph->addEdge(1,2,5);
    graph->addEdge(3,2,5);
    graph->addEdge(3,0,2);
    graph->addEdge(3,1,2);
    graph->addEdge(0,1,2);
    graph->addEdge(0,2,2);

    std::vector<Edge> *edgesGet = graph->getEdges();
    ASSERT_EQ(6, edgesGet->size());

}

TEST_F(GraphTest, whenComparingEdges_mustDoItAsExpected2){
    Edge edge = Edge(1,2,4);
    Edge other = Edge(2,1,4);

    ASSERT_TRUE(edge == other);
}

TEST_F(GraphTest, whenGettingAllEdges_mustNotReturnDuplicated){
    graph->resetSize(10);
    graph->addEdge(2,3,5);
    graph->addEdge(4,5,6);
    graph->addEdge(7,6,8);

    std::vector<Edge> *edges = graph->getEdges();

    ASSERT_EQ(3, edges->size());
}

TEST_F(GraphTest, whenComparingEdgesSet_mustCompareOk1){
    graph->resetSize(2);
    graph->addEdge(0,1,3);
    graph->addEdge(1,0,3);

    std::vector<Edge> *edges = graph->getEdges();

    ASSERT_EQ(1, edges->size());
}

TEST_F(GraphTest, whenComparingEdgesSet_mustCompareOk2){
    graph->resetSize(2);
    graph->addEdge(0,1,2);
    graph->addEdge(0,1,2);

    std::vector<Edge> *edges = graph->getEdges();

    ASSERT_EQ(1, edges->size());
}

TEST_F(GraphTest, whenComparingEdgesSet_mustCompareOk3){
    graph->resetSize(2);
    graph->addEdge(0,1,2);
    graph->addEdge(0,1,3);

    std::vector<Edge> *edges = graph->getEdges();

    ASSERT_EQ(1, edges->size());
}

TEST_F(GraphTest, whenComparingEdgesSet_mustCompareOk){
    graph->resetSize(3);
    graph->addEdge(0,2,4);
    graph->addEdge(1,0,3);

    std::vector<Edge> *edges = graph->getEdges();

    ASSERT_EQ(2, edges->size());
}

TEST_F(GraphTest, whenComparingEdgesSet_mustCompareOk5){
    graph->resetSize(3);
    graph->addEdge(0,1,5);
    graph->addEdge(0,2,200);
    graph->addEdge(1,2,5);

    std::vector<Edge> *edges = graph->getEdges();

    ASSERT_EQ(3, edges->size());
}

TEST_F(GraphTest,whenSorting_mustDoItAsExpected){
    graph->resetSize(3);
    graph->addEdge(0,1,5);
    graph->addEdge(0,2,200);
    graph->addEdge(1,2,5);
    std::vector<Edge> *edges = graph->getEdges();

    sort(edges->begin(),edges->end());

    ASSERT_EQ(3, edges->size());
    ASSERT_TRUE(edges->at(0).getEdgeCost() == 5);
    ASSERT_TRUE(edges->at(1).getEdgeCost() == 5);
    ASSERT_TRUE(edges->at(2).getEdgeCost() == 200);
}