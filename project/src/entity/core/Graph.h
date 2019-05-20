//
// Created by Christian nahuel Rivera on 12/5/19.
//

#ifndef AED3_2019_1C_TP2_GRAPH_H
#define AED3_2019_1C_TP2_GRAPH_H

#include <vector>
#include "Edge.h"

class Graph {
public:
    virtual int getVertex() = 0;
    virtual bool adjacent(int vertexIndex1, int vertexIndex2) = 0;
    virtual void addEdge(int vertexIndex1, int vertexIndex2, long edgeCost) = 0;
    virtual std::vector<Edge> *getEdges() = 0; // allocates new pointer that should be deleted afterwards
    virtual long getTotalCost() = 0;
    virtual void resetSize(int newVerticesSize) = 0;
    virtual ~Graph() = default;
};
#endif //AED3_2019_1C_TP2_GRAPH_H
