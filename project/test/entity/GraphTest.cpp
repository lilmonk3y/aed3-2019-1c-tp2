//
// Created by Christian nahuel Rivera on 12/5/19.
//
#include "gtest/gtest.h"
#include "../../src/entity/core/Graph.h"
#include "../../src/entity/core/AdjacencyListGraph.h"
#include "../../src/entity/auxiliar/DirectedTreeGraph.h"

struct GraphTest : testing::Test{
    Graph *graph;

    GraphTest(){
        graph = new AdjacencyListGraph(1);
    }

    ~GraphTest(){
        delete graph;
    }
};

TEST_F(GraphTest, whenInstanciatinAGraph_mustDoItAsExpected){
    graph->resetSize(10);

    ASSERT_EQ(10, graph->getVertexSize());
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

    std::set<Edge>* edgesGet= graph->getEdgeSet();
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

    std::set<Edge>* edges = graph->getEdgeSet();

    ASSERT_EQ(3, edges->size());
}

TEST_F(GraphTest, whenComparingEdgesSet_mustCompareOk1){
    graph->resetSize(2);
    graph->addEdge(0,1,3);
    graph->addEdge(1,0,3);

    std::set<Edge> *edges = graph->getEdgeSet();

    ASSERT_EQ(1, edges->size());
}

TEST_F(GraphTest, whenComparingEdgesSet_mustCompareOk2){
    graph->resetSize(2);
    graph->addEdge(0,1,2);
    graph->addEdge(0,1,2);

    std::set<Edge> *edges = graph->getEdgeSet();

    ASSERT_EQ(1, edges->size());
}

TEST_F(GraphTest, whenComparingEdgesSet_mustCompareOk3){
    graph->resetSize(2);
    graph->addEdge(0,1,2);
    graph->addEdge(1,0,2);

    std::set<Edge> *edges = graph->getEdgeSet();

    ASSERT_EQ(1, edges->size());
}

TEST_F(GraphTest, whenComparingEdgesSet_mustCompareOk){
    graph->resetSize(3);
    graph->addEdge(0,2,4);
    graph->addEdge(1,0,3);

    std::set<Edge> *edges = graph->getEdgeSet();

    ASSERT_EQ(2, edges->size());
}

TEST_F(GraphTest, whenComparingEdgesSet_mustCompareOk5){
    graph->resetSize(3);
    graph->addEdge(0,1,5);
    graph->addEdge(0,2,200);
    graph->addEdge(1,2,5);

    std::set<Edge> *edges = graph->getEdgeSet();

    ASSERT_EQ(3, edges->size());
}

TEST_F(GraphTest,whenSorting_mustDoItAsExpected){
    graph->resetSize(3);
    graph->addEdge(0,1,5);
    graph->addEdge(0,2,200);
    graph->addEdge(1,2,5);

    std::set<Edge> *edges = graph->getEdgeSet();
    //sort(edges->begin(),edges->end());

    ASSERT_EQ(3, edges->size());
    auto iter = edges->begin();
    ASSERT_TRUE(iter.operator*().getEdgeCost() == 5);
    iter++;
    ASSERT_TRUE(iter.operator*().getEdgeCost() == 200);
    iter++;
    ASSERT_TRUE(iter.operator*().getEdgeCost() == 5);
}

TEST_F(GraphTest, sorting_testting1){
    graph->resetSize(4);

    graph->addEdge(1,2,5);
    graph->addEdge(3,2,5);
    graph->addEdge(3,0,2);
    graph->addEdge(3,1,2);
    graph->addEdge(0,1,2);
    graph->addEdge(0,2,2);

    std::set<Edge>* edgesGet= graph->getEdgeSet();

    ASSERT_EQ(6, edgesGet->size());
    auto iter = edgesGet->begin();
    ASSERT_EQ(Edge(0,1,2), iter.operator*());
    iter++;
    ASSERT_EQ(Edge(0,2,2), iter.operator*());
    iter++;
    ASSERT_EQ(Edge(0,3,2), iter.operator*());
    iter++;
    ASSERT_EQ(Edge(1,2,5), iter.operator*());
    iter++;
    ASSERT_EQ(Edge(1,3,2), iter.operator*());
    iter++;
    ASSERT_EQ(Edge(2,3,5), iter.operator*());
}

TEST_F(GraphTest, sortingByCost_testing1){
    graph->resetSize(8);

    graph->addEdge(0,1,11);
    graph->addEdge(0,2,9);
    graph->addEdge(0,3,6);
    graph->addEdge(1,3,5);
    graph->addEdge(1,4,7);
    graph->addEdge(2,3,12);
    graph->addEdge(2,5,6);
    graph->addEdge(3,5,3);
    graph->addEdge(3,4,4);
    graph->addEdge(3,6,7);
    graph->addEdge(4,6,2);
    graph->addEdge(5,6,8);
    graph->addEdge(5,7,10);
    graph->addEdge(6,7,6);

    set<Edge>* edges = graph->getEdgeSet();
    vector<Edge> edgesSortedByCost = vector<Edge>(edges->begin(), edges->end()); // O(E)
    sort(edgesSortedByCost.begin(), edgesSortedByCost.end(), edgeComparatorByCost); // O(E * log(E))

    ASSERT_EQ(14, edgesSortedByCost.size());
    auto iter = edgesSortedByCost.begin();
    ASSERT_EQ(2, iter.operator*().getEdgeCost());
    iter++;
    ASSERT_EQ(3, iter.operator*().getEdgeCost());
    iter++;
    ASSERT_EQ(4, iter.operator*().getEdgeCost());
    iter++;
    ASSERT_EQ(5, iter.operator*().getEdgeCost());
    iter++;
    ASSERT_EQ(6, iter.operator*().getEdgeCost());
    iter++;
    ASSERT_EQ(6, iter.operator*().getEdgeCost());
    iter++;
    ASSERT_EQ(6, iter.operator*().getEdgeCost());
    iter++;
    ASSERT_EQ(7, iter.operator*().getEdgeCost());
    iter++;
    ASSERT_EQ(7, iter.operator*().getEdgeCost());
    iter++;
    ASSERT_EQ(8, iter.operator*().getEdgeCost());
    iter++;
    ASSERT_EQ(9, iter.operator*().getEdgeCost());
    iter++;
    ASSERT_EQ(10, iter.operator*().getEdgeCost());
    iter++;
    ASSERT_EQ(11, iter.operator*().getEdgeCost());
    iter++;
    ASSERT_EQ(12, iter.operator*().getEdgeCost());
    iter++;
}