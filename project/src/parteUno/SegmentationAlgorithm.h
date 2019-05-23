//
// Created by Axel Arrondo on 2019-05-23.
//

#ifndef AED3_2019_1C_TP2_SEGMENTATIONALGORITHM_H
#define AED3_2019_1C_TP2_SEGMENTATIONALGORITHM_H

#include "../entity/core/Graph.h"
#include "../utils/DisjoinSet.h"
#include "../entity/core/AdjacencyListGraph.h"
#include "../utils/ArrayDisjoinSet.h"

class SegmentationAlgorithm {
public:
    Graph * segmentateGraphImage(Graph *graph);

private:

    int minInternalDifference(int componentI, int componentJ);
    int internalDifference(int component);
    int tau(int component);
    int cardinal(DisjoinSet* disjoinSet, int component);
};


#endif //AED3_2019_1C_TP2_SEGMENTATIONALGORITHM_H
