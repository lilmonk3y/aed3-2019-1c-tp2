//
// Created by Christian nahuel Rivera on 12/5/19.
//

#ifndef AED3_2019_1C_TP2_GETMST_H
#define AED3_2019_1C_TP2_GETMST_H

#include "../entity/Graph.h"
#include "DisjoinSet.h"

class GetMST{
public:
    GetMST(DisjoinSet *disjoinSetStrategy);
    Graph * getMST(Graph *graph);

private:
    DisjoinSet *disjoinSet;
};

#endif //AED3_2019_1C_TP2_GETMST_H
