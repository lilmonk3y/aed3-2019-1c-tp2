#include "gtest/gtest.h"
#include "../../src/parteUno/SegmentationAlgorithm.h"
#include "../../src/utils/DisjoinSet.h"
#include "../../src/utils/ArrayDisjoinSet.h"
#include "../../src/utils/GetMST.h"
#include <set>
#include <map>
using namespace std;


struct SegmentationAlgorithmTest : testing::Test{
    SegmentationAlgorithm* segmentationAlgorithm;

    SegmentationAlgorithmTest(){
        AdjacencyListGraph* grafo =  new AdjacencyListGraph(4);
        segmentationAlgorithm = new SegmentationAlgorithm(grafo);
    }

    ~SegmentationAlgorithmTest(){
        delete segmentationAlgorithm;
    }
};


TEST_F(SegmentationAlgorithmTest, simpleSegmentationWorks){
    AdjacencyListGraph* grafo =  new AdjacencyListGraph(4);
    grafo->addEdge(0, 1, 0);
    grafo->addEdge(1, 2, 255);
    grafo->addEdge(2, 3, 255);
    grafo->addEdge(3, 1, 255);

    segmentationAlgorithm = new SegmentationAlgorithm(grafo);
    DisjoinSet* disjointSet = segmentationAlgorithm->graphSementationIntoSets();

    ASSERT_TRUE(disjointSet->find(0) == disjointSet->find(1) );
    ASSERT_TRUE(disjointSet->find(1) != disjointSet->find(2) &&  disjointSet->find(2) != disjointSet->find(3));
}