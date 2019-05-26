#include "gtest/gtest.h"
#include "../../src/parteUno/SegmentationAlgorithm.h"
#include "../../src/entity/core/Graph.h"
#include "../../src/entity/core/Graph.h"
#include "../../src/utils/DisjoinSet.h"
#include "../../src/entity/core/AdjacencyListGraph.h"
#include "../../src/utils/ArrayDisjoinSet.h"
#include "../../src/utils/GetMST.h"
#include <set>
#include <map>
using namespace std;


struct SegmentationAlgorithmTest : testing::Test{
    SegmentationAlgorithm* segmentationAlgorithm;

    SegmentationAlgorithmTest(){
    }

    ~SegmentationAlgorithmTest(){
        delete segmentationAlgorithm;
    }
};


TEST_F(SegmentationAlgorithmTest, segmentationWorks){
    Graph* graph =  new AdjacencyListGraph(4);
    graph->addEdge(0, 1, 0);
    graph->addEdge(1, 2, 255);
    graph->addEdge(2, 3, 0);
    graph->addEdge(3, 1, 0);

    DisjoinSet& disjointSet = segmentationAlgorithm->graphSementationIntoSets(*graph);
        graph->resetSize(10);

        graph->addEdge(2, 3, 5);

        ASSERT_TRUE(disjointSet.find(0)!=disjointSet.find(1));
        ASSERT_TRUE(disjointSet.find(0)==disjointSet.find(2) && disjointSet.find(2)==disjointSet.find(3));
}