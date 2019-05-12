//
// Created by Christian nahuel Rivera on 12/5/19.
//

#ifndef AED3_2019_1C_TP2_GRAPH_H
#define AED3_2019_1C_TP2_GRAPH_H

class Graph {
public:
    virtual int getVertex() = 0;
    virtual bool adjacent(int vertexIndex1, int vertexIndex2) = 0;
    virtual void addEdge(int vertexIndex1, int vertexIndex2, long edgeCost) = 0;
};
#endif //AED3_2019_1C_TP2_GRAPH_H
