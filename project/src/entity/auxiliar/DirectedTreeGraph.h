//
// Created by Christian nahuel Rivera on 15/5/19.
//

#ifndef AED3_2019_1C_TP2_TREEGRAPH_H
#define AED3_2019_1C_TP2_TREEGRAPH_H


#include "../core/Graph.h"
#include "TreeNode.h"

class DirectedTreeGraph{
public:
    explicit DirectedTreeGraph(int vertexSize);
    void addToComponent(int fatherIndex, int sonIndex);
    TreeNode *getIndex(int index);

    bool adjacent(int vertexIndex1, int vertexIndex2) ;
    void resetSize(int newVerticesSize) ;
    int getVertex() ;
private:
    std::vector<TreeNode*> vertices;

    void updateMySonsComponent(int sonIndex) const;
};


#endif //AED3_2019_1C_TP2_TREEGRAPH_H
