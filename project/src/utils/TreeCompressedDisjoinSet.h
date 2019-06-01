//
// Created by Christian nahuel Rivera on 18/5/19.
//

#ifndef AED3_2019_1C_TP2_TREECOMPRESSEDDISJOINSET_H
#define AED3_2019_1C_TP2_TREECOMPRESSEDDISJOINSET_H


#include "DisjoinSet.h"
#include "../entity/auxiliar/DirectedTreeGraph.h"

class TreeCompressedDisjoinSet : public DisjoinSet {
public:
    /*
     * O(n)
     */
    void create(Graph *graph) override;
    /*
     * complejidad O(ahpha(n)) que es una función casi constante
    */
    int find(int vertex) override;
    /*
     * complejidad O(ahpha(n)) que es una función casi constante
    */
    void join(int alreadyIn, int newNode) override;

private:
    DirectedTreeGraph* components;
    std::vector<int> heights;
};


#endif //AED3_2019_1C_TP2_TREECOMPRESSEDDISJOINSET_H
