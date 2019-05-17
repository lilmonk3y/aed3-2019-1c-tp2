//
// Created by Christian nahuel Rivera on 15/5/19.
//

#ifndef AED3_2019_1C_TP2_TREENODE_H
#define AED3_2019_1C_TP2_TREENODE_H


#include <vector>
#include "TreeEdge.h"

class TreeNode {
public:
    TreeNode(int vertexIndex);
    void addAdjacent(TreeNode adjacent, long edgeCost);
    std::vector<TreeEdge> getAdyacentNodes();
    int getVertexIndex();
    int getAdjacentCount();
private:
    std::vector<TreeEdge> adjacentNodes;
    int vertexIndex;
    int adjacentCount;
};


#endif //AED3_2019_1C_TP2_TREENODE_H
