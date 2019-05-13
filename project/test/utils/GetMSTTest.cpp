//
// Created by Christian nahuel Rivera on 12/5/19.
//

#include "gtest/gtest.h"
#include "../../src/entity/Graph.h"
#include "../../src/entity/AdjacencyListGraph.h"
#include "../../src/utils/GetMST.h"
#include "../../src/utils/DefaultDisjoinSet.h"


struct MSTTest : testing::Test {
    GetMST *getMST;
    Graph *graph;
    Graph *graph1;
    Graph *graph2;

    MSTTest(){
        getMST = new GetMST(new DisjoinSetDefault());
        //getMST = new GetMST(new DisjoinSetCompressed());

        graph1 = new AdjacencyListGraph(4);
        graph1->addEdge(0,1, 3);
        graph1->addEdge(0,3, 5);
        graph1->addEdge(1,2, 8);
        graph1->addEdge(1,3, 1);
        graph1->addEdge(2,3, 2);

        graph2 = new AdjacencyListGraph(9);
        graph2->addEdge(0,1, 4);
        graph2->addEdge(0,7, 8);
        graph2->addEdge(1,7, 11);
        graph2->addEdge(1,2, 8);
        graph2->addEdge(2,3, 7);
        graph2->addEdge(2,5, 4);
        graph2->addEdge(2,8, 2);
        graph2->addEdge(3,4, 9);
        graph2->addEdge(3,5, 14);
        graph2->addEdge(4,5, 10);
        graph2->addEdge(5,6, 2);
        graph2->addEdge(6,7, 1);
        graph2->addEdge(6,8, 6);
        graph2->addEdge(7,8, 7);

    }

    ~MSTTest(){
        delete getMST;
        delete graph;
        delete graph1;
        delete graph2;
    }
};

TEST_F(MSTTest,whenGetPrimMSTOfATree_mustReturnTheSameGraph){
    graph = new AdjacencyListGraph(2);
    graph->addEdge(0,1,5);

    Graph *actualMST = getMST->getMST(graph);

    Graph *expectedMST = new AdjacencyListGraph(2);
    expectedMST->addEdge(0,1,5);
    ASSERT_EQ(actualMST->getTotalCost(), expectedMST->getTotalCost());
}

TEST_F(MSTTest,whenGetPrimMSTOfACircuit_mustReturnAnMSTOfTheOriginalGraph){
    // A circuit of 3 nodes
    graph = new AdjacencyListGraph(3);
    graph->addEdge(0,1,5);
    graph->addEdge(0,2,200);
    graph->addEdge(1,2,5);

    Graph *actualMST = getMST->getMST(graph);

    Graph *expectedMST = new AdjacencyListGraph(3);
    expectedMST->addEdge(0,1,5);
    expectedMST->addEdge(1,2,5);
    ASSERT_EQ(expectedMST->getTotalCost() , actualMST->getTotalCost());
}

TEST_F(MSTTest,whenGetKruskalDefaultMSTOfATree_mustReturnTheSameGraph){
    graph= new AdjacencyListGraph(2);
    graph->addEdge(0,1,5);

    Graph *actualMST = getMST->getMST(graph);

    Graph *expectedMST= new AdjacencyListGraph(2);
    expectedMST->addEdge(0,1,5);
    ASSERT_EQ(actualMST->getTotalWeight(),expectedMST->getTotalWeight());
}

TEST_F(MSTTest,whenGetKruskalDefaultMSTOfACircuit_mustReturnAnMSTOfTheOriginalGraph){
    // A circuit of 3 nodes
    graph->build(3);
    graph->addEdge(Node(0),Node(1),5);
    graph->addEdge(Node(0),Node(2),200);
    graph->addEdge(Node(1),Node(2),5);

    graph->setMSTStrategy(new KruskalDefaultMST());
    Graph actualMST = graph->getMST();

    Graph expectedMST(3);
    expectedMST.addEdge(Node(0),Node(1),5);
    expectedMST.addEdge(Node(1),Node(2),5);
    ASSERT_EQ(expectedMST.getTotalWeight() , actualMST.getTotalWeight());
}

TEST_F(MSTTest,whenGetKruskalCompressedMSTOfATree_mustReturnTheSameGraph){
    graph->build(2);
    graph->addEdge(Node(0),Node(1),5);

    graph->setMSTStrategy(new KruskalCompressedMST());
    Graph actualMST = graph->getMST();

    Graph expectedMST(2);
    expectedMST.addEdge(Node(0),Node(1),5);
    ASSERT_EQ(actualMST.getTotalWeight(),expectedMST.getTotalWeight());
}

TEST_F(MSTTest,whenGetKruskalCompressedMSTOfACircuit_mustReturnAnMSTOfTheOriginalGraph){
    // A circuit of 3 nodes
    graph->build(3);
    graph->addEdge(Node(0),Node(1),5);
    graph->addEdge(Node(0),Node(2),200);
    graph->addEdge(Node(1),Node(2),5);

    graph->setMSTStrategy(new KruskalCompressedMST());
    Graph actualMST = graph->getMST();

    Graph expectedMST(3);
    expectedMST.addEdge(Node(0),Node(1),5);
    expectedMST.addEdge(Node(1),Node(2),5);
    ASSERT_EQ(expectedMST.getTotalWeight() , actualMST.getTotalWeight());
}

TEST_F(MSTTest, whenGraph1PrimMST_shouldHaveTotalWeight6)
{
    graph1->setMSTStrategy(new PrimMST());
    auto mst = graph1->getMST();

    float actualWeight = mst.getTotalWeight();
    ASSERT_EQ(6, actualWeight);
}

TEST_F(MSTTest, whenGraph2PrimMST_shouldHaveTotalWeight37)
{
    graph2->setMSTStrategy(new PrimMST());
    auto mst = graph2->getMST();

    float actualWeight = mst.getTotalWeight();
    ASSERT_EQ(37, actualWeight);
}

TEST_F(MSTTest, whenGraph1KruskalDefaultMST_shouldHaveTotalWeight6)
{
    graph1->setMSTStrategy(new KruskalDefaultMST());
    auto mst = graph1->getMST();

    float actualWeight = mst.getTotalWeight();
    ASSERT_EQ(6, actualWeight);
}

TEST_F(MSTTest, whenGraph2KruskalDefaultMST_shouldHaveTotalWeight37)
{
    graph2->setMSTStrategy(new KruskalDefaultMST());
    auto mst = graph2->getMST();

    float actualWeight = mst.getTotalWeight();
    ASSERT_EQ(37, actualWeight);
}

TEST_F(MSTTest, whenGraph1KruskalCompressedMST_shouldHaveTotalWeight6)
{
    graph1->setMSTStrategy(new KruskalCompressedMST());
    auto mst = graph1->getMST();

    float actualWeight = mst.getTotalWeight();
    ASSERT_EQ(6, actualWeight);
}

TEST_F(MSTTest, whenGraph2KruskalCompressedMST_shouldHaveTotalWeight37)
{
    graph2->setMSTStrategy(new KruskalCompressedMST());
    auto mst = graph2->getMST();

    float actualWeight = mst.getTotalWeight();
    ASSERT_EQ(37, actualWeight);
}