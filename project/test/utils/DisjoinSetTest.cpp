//
// Created by Christian nahuel Rivera on 12/5/19.
//

#include "gtest/gtest.h"
#include "../../src/utils/DisjoinSet.h"
#include "../../src/utils/DefaultDisjoinSet.h"
#include "../../src/entity/AdjacencyListGraph.h"
#include "../../src/utils/CompressedDisjoinSet.h"

struct DisSetTest : testing::Test{
    DisjoinSet *disjoinSet;
    DisSetTest(){
        //disjoinSet = new DisjoinSetDefault();
        disjoinSet = new DisjoinSetCompressed();
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
}

TEST_F(DisSetTest, whenJoiningTwoComponents_mustPutThemTheSameComponentId){
    Graph* graph = new AdjacencyListGraph(3);
    disjoinSet->create(graph);

    disjoinSet->join(0,1);

    ASSERT_EQ(0, disjoinSet->find(0));
    ASSERT_EQ(0, disjoinSet->find(1));
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
}