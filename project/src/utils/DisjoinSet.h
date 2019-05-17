//
// Created by Christian nahuel Rivera on 12/5/19.
//

#ifndef AED3_2019_1C_TP2_DISJOINSET_H
#define AED3_2019_1C_TP2_DISJOINSET_H


#include "../entity/core/Graph.h"

class DisjoinSet {
public:
    virtual int find(int vertexIndex) = 0;
    virtual void join(int alreadyIn, int newNode) = 0;
    virtual void create(Graph *graph) = 0;
    virtual ~DisjoinSet() { };

};

#endif //AED3_2019_1C_TP2_DISJOINSET_H
