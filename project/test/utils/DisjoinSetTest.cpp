//
// Created by Christian nahuel Rivera on 12/5/19.
//

#include "gtest/gtest.h"
#include "../../src/utils/DisjoinSet.h"
#include "../../src/utils/ArrayDisjoinSet.h"
#include "../../src/entity/core/AdjacencyListGraph.h"
#include "../../src/utils/ArrayCompressedDisjoinSet.h"
#include "../../src/utils/TreeDisjoinSet.h"
#include "../../src/utils/TreeCompressedDisjoinSet.h"

struct DisSetTest : testing::Test{
    DisjoinSet *disjoinSet;

    DisSetTest(){
        disjoinSet = new ArrayDisjoinSet();
        //disjoinSet = new ArrayCompressedDisjoinSet();
        //disjoinSet = new TreeDisjoinSet();
        //disjoinSet = new TreeCompressedDisjoinSet();
    }
    ~DisSetTest(){
        delete disjoinSet;
    }
};

TEST_F(DisSetTest,whenCreateADisjoinSet_mustAddEveryNodeIntoADifferentComponent){
    Graph* graph = new AdjacencyListGraph(3);

    disjoinSet->create(graph);

    ASSERT_EQ(0, disjoinSet->find(0));
    ASSERT_EQ(1, disjoinSet->find(1));
    ASSERT_EQ(2, disjoinSet->find(2));

    delete graph;
}

TEST_F(DisSetTest, whenJoiningTwoComponents_mustPutThemTheSameComponentId){
    Graph* graph = new AdjacencyListGraph(3);
    disjoinSet->create(graph);

    disjoinSet->join(0,1);

    ASSERT_EQ(0, disjoinSet->find(0));
    ASSERT_EQ(0, disjoinSet->find(1));

    delete graph;
}

TEST_F(DisSetTest, whenJoiningComponentsWithMoreThanOneElement_mustPutTheSameIdToAllElements){
    Graph* graph = new AdjacencyListGraph(6);
    disjoinSet->create(graph);
    disjoinSet->join(0,1);
    disjoinSet->join(2,3);
    disjoinSet->join(4,5);

    // En este momento tengo un disjoinSet con 3 componentes conexas: 0-1, 2-3 y 4-5
    disjoinSet->join(0,2);
    disjoinSet->join(0,4);

    // Junté todos los ejes entán en la misma componente conexa
    ASSERT_EQ(0, disjoinSet->find(0));
    ASSERT_EQ(0, disjoinSet->find(1));
    ASSERT_EQ(0, disjoinSet->find(2));
    ASSERT_EQ(0, disjoinSet->find(3));
    ASSERT_EQ(0, disjoinSet->find(4));
    ASSERT_EQ(0, disjoinSet->find(5));

    delete graph;
}

TEST_F(DisSetTest,whenJoiningComponentsWithSons_mustAddSonsToComponent){
    Graph* graph = new AdjacencyListGraph(6);
    disjoinSet->create(graph);

    disjoinSet->join(4,5);
    disjoinSet->join(3,4);
    disjoinSet->join(2,3);

    ASSERT_EQ(2, disjoinSet->find(3));
    ASSERT_EQ(2, disjoinSet->find(5));
    ASSERT_EQ(2, disjoinSet->find(4));
    ASSERT_EQ(2, disjoinSet->find(2));

    delete graph;
}

TEST_F(DisSetTest,testing1){
    Graph* graph = new AdjacencyListGraph(6);
    disjoinSet->create(graph);

    disjoinSet->join(5,0);
    disjoinSet->join(3,4);
    disjoinSet->join(1,2);
    disjoinSet->join(1,3);
    disjoinSet->join(3,5);

    ASSERT_EQ(1, disjoinSet->find(1));
    ASSERT_EQ(1, disjoinSet->find(2));
    ASSERT_EQ(1, disjoinSet->find(3));
    ASSERT_EQ(1, disjoinSet->find(4));
    ASSERT_EQ(1, disjoinSet->find(5));
    ASSERT_EQ(1, disjoinSet->find(0));

    delete graph;
}

TEST_F(DisSetTest,testing2){
    Graph* graph = new AdjacencyListGraph(10);
    disjoinSet->create(graph);

    disjoinSet->join(0,1);
    disjoinSet->join(8,9);
    disjoinSet->join(7,9);
    disjoinSet->join(6,9);
    disjoinSet->join(5,9);
    disjoinSet->join(4,9);
    disjoinSet->join(3,9);
    disjoinSet->join(2,9);
    disjoinSet->join(1,9);
    disjoinSet->join(0,9);

    ASSERT_EQ(0,disjoinSet->find(0));
    ASSERT_EQ(0,disjoinSet->find(1));
    ASSERT_EQ(0,disjoinSet->find(2));
    ASSERT_EQ(0,disjoinSet->find(3));
    ASSERT_EQ(0,disjoinSet->find(4));
    ASSERT_EQ(0,disjoinSet->find(5));
    ASSERT_EQ(0,disjoinSet->find(6));
    ASSERT_EQ(0,disjoinSet->find(7));
    ASSERT_EQ(0,disjoinSet->find(8));
    ASSERT_EQ(0,disjoinSet->find(9));

    delete graph;
}

TEST_F(DisSetTest, testing3){
    Graph* graph = new AdjacencyListGraph(20);
    disjoinSet->create(graph);

    disjoinSet->join(18,19);
    disjoinSet->join(16,17);
    disjoinSet->join(14,15);
    disjoinSet->join(12,13);
    disjoinSet->join(10,11);
    disjoinSet->join(8,9);
    disjoinSet->join(6,7);
    disjoinSet->join(4,5);
    disjoinSet->join(2,3);
    disjoinSet->join(0,1);
    disjoinSet->join(9,19);
    disjoinSet->join(7,17);
    disjoinSet->join(5,15);
    disjoinSet->join(3,13);
    disjoinSet->join(1,11);
    disjoinSet->join(7,19);
    disjoinSet->join(3,15);
    disjoinSet->join(1,13);
    disjoinSet->join(0,19);
    disjoinSet->join(0,15);

    ASSERT_EQ(0, disjoinSet->find(0));
    ASSERT_EQ(0, disjoinSet->find(1));
    ASSERT_EQ(0, disjoinSet->find(2));
    ASSERT_EQ(0, disjoinSet->find(3));
    ASSERT_EQ(0, disjoinSet->find(4));
    ASSERT_EQ(0, disjoinSet->find(5));
    ASSERT_EQ(0, disjoinSet->find(6));
    ASSERT_EQ(0, disjoinSet->find(7));
    ASSERT_EQ(0, disjoinSet->find(8));
    ASSERT_EQ(0, disjoinSet->find(9));
    ASSERT_EQ(0, disjoinSet->find(10));
    ASSERT_EQ(0, disjoinSet->find(11));
    ASSERT_EQ(0, disjoinSet->find(12));
    ASSERT_EQ(0, disjoinSet->find(13));
    ASSERT_EQ(0, disjoinSet->find(14));
    ASSERT_EQ(0, disjoinSet->find(15));
    ASSERT_EQ(0, disjoinSet->find(16));
    ASSERT_EQ(0, disjoinSet->find(17));
    ASSERT_EQ(0, disjoinSet->find(18));
    ASSERT_EQ(0, disjoinSet->find(19));

    delete graph;
}