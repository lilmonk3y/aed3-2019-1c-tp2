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
    std::set<int>* getSet(int indexComponent);

private:
    DirectedTreeGraph* components;
    std::vector<int> heights;
    std::vector<std::set<int>*>* sets;
    void unionSetLeft(std::set<int>* aSet ,std::set<int>* bSet);
};


#endif //AED3_2019_1C_TP2_TREECOMPRESSEDDISJOINSET_H
