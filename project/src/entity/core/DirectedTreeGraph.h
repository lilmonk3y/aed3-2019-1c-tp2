//
// Created by Christian nahuel Rivera on 15/5/19.
//

#ifndef AED3_2019_1C_TP2_TREEGRAPH_H
#define AED3_2019_1C_TP2_TREEGRAPH_H


#include "Graph.h"
#include "../auxiliar/TreeNode.h"

class DirectedTreeGraph : public Graph {
public:
    DirectedTreeGraph(int vertexSize);
    int getVertex() override;
    bool adjacent(int vertexIndex1, int vertexIndex2) override;
    void addEdge(int vertexIndex1, int vertexIndex2, long edgeCost) override;
    std::vector<Edge> *getEdges() override;
    long getTotalCost() override;
    void resetSize(int newVerticesSize) override;
    int getIndex(int index);
private:
    std::vector<TreeNode> vertices;

    bool alreadyInserted(std::vector<Edge> *edges, Edge *edge);
};


#endif //AED3_2019_1C_TP2_TREEGRAPH_H
