//
// Created by Christian nahuel Rivera on 17/5/19.
//

#ifndef AED3_2019_1C_TP2_TREEDISJOINSET_H
#define AED3_2019_1C_TP2_TREEDISJOINSET_H


#include "DisjoinSet.h"
#include "../entity/auxiliar/DirectedTreeGraph.h"

class TreeDisjoinSet : public DisjoinSet {
public:
    int find(int vertex) override;
    void join(int alreadyIn, int newNode) override;
    void create(Graph *graph) override;

private:
    DirectedTreeGraph *components;
};


#endif //AED3_2019_1C_TP2_TREEDISJOINSET_H
