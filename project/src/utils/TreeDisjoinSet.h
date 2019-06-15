//
// Created by Christian nahuel Rivera on 17/5/19.
//

#ifndef AED3_2019_1C_TP2_TREEDISJOINSET_H
#define AED3_2019_1C_TP2_TREEDISJOINSET_H


#include "DisjoinSet.h"
#include "../entity/auxiliar/DirectedTreeGraph.h"

class TreeDisjoinSet : public DisjoinSet {
public:
    /*
     * O(1)
     */
    int find(int vertex) override;
    /*
     * O(n) por hacer update de todos los hijos del newNode
     */
    void join(int alreadyIn, int newNode) override;
    /*
     * O(n)
     */
    void create(Graph *graph) override;

    ~TreeDisjoinSet();

private:
    DirectedTreeGraph *components;
};


#endif //AED3_2019_1C_TP2_TREEDISJOINSET_H
