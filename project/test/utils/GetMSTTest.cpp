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

TEST_F(MSTTest,whenGetPrimMSTOfACircuit_mustReturnAnMSTOfTheOriginalGraph){
    // A circuit of 3 nodes
    graph = new AdjacencyListGraph(3);
    graph->addEdge(0,1,5);
    graph->addEdge(0,2,200);
    graph->addEdge(1,2,5);

    Graph *actualMST = getMST->getMST(graph);

    ASSERT_EQ(10 , actualMST->getTotalCost());
}

TEST_F(MSTTest,whenGetKruskalCompressedMSTOfATree_mustReturnTheSameGraph){
    graph= new AdjacencyListGraph(2);
    graph->addEdge(0,1,5);

    Graph *actualMST = getMST->getMST(graph);

    ASSERT_EQ(5,actualMST->getTotalCost());
}

TEST_F(MSTTest, whenGraph1PrimMST_shouldHaveTotalWeight6)
{
    auto mst = getMST->getMST(graph1);

    float actualWeight = mst->getTotalCost();
    ASSERT_EQ(6, actualWeight);
}

TEST_F(MSTTest, whenGraph2PrimMST_shouldHaveTotalWeight37)
{
    auto mst = getMST->getMST(graph2);

    float actualWeight = mst->getTotalCost();
    ASSERT_EQ(37, actualWeight);
}