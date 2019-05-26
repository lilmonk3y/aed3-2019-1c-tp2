#include "gtest/gtest.h"
#include "../../src/parteUno/SegmentationAlgorithm.h"
#include "../../src/entity/core/Graph.h"
#include "../entity/core/Graph.h"
#include "../utils/DisjoinSet.h"
#include "../entity/core/AdjacencyListGraph.h"
#include "../utils/ArrayDisjoinSet.h"
#include "../utils/GetMST.h"
#include <set>
#include <map>
using namespace std;


struct SegmentationAlgorithm : testing::Test{
    SegmentationAlgorithm* segmentationAlgorithm;

    SegmentationAlgorithmTest(){
    }

    ~SegmentationAlgorithmTest(){
        delete segmentationAlgorithm;
    }
};


TEST_F(GraphTest, segmentationWorks){
    Graph& graph =  new AdjacencyListGraph(4);
    graph->addEdge(0, 1, 0);
    graph->addEdge(1, 2, 255);
    graph->addEdge(2, 3, 0);
    graph->addEdge(3, 1, 0);

    DisjoinSet& disjointSet = graphSementationIntoSets(Graph& graph);
        graph->resetSize(10);

        graph->addEdge(2, 3, 5);

        ASSERT_TRUE(disjointSet.find(0)!=disjointSet.find(1));
        ASSERT_TRUE(disjointSet.find(0)==disjointSet.find(2) AND disjointSet.find(2)==disjointSet.find(3));
}