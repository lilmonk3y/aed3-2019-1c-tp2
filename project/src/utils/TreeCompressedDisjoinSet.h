//
// Created by Christian nahuel Rivera on 18/5/19.
//

#ifndef AED3_2019_1C_TP2_TREECOMPRESSEDDISJOINSET_H
#define AED3_2019_1C_TP2_TREECOMPRESSEDDISJOINSET_H


#include "DisjoinSet.h"
#include "../entity/auxiliar/DirectedTreeGraph.h"

class TreeCompressedDisjoinSet : public DisjoinSet {
public:
    void create(Graph *graph) override;
    int find(int vertex) override;
    void join(int alreadyIn, int newNode) override;

private:
    DirectedTreeGraph* components;
    std::vector<int> heights;
};


#endif //AED3_2019_1C_TP2_TREECOMPRESSEDDISJOINSET_H
