//
// Created by Christian nahuel Rivera on 15/5/19.
//

#include "../TreeNode.h"

void TreeNode::addAdjacent(TreeNode adjacent, long edgeCost) {
    this->adjacentNodes.emplace_back(adjacent.getVertexIndex(),edgeCost);
    this->adjacentCount++;
}

std::vector<TreeEdge> TreeNode::getAdyacentNodes() {
    return this->adjacentNodes;
}

TreeNode::TreeNode(int vertexIndex) {
    this->vertexIndex = vertexIndex;
    this->adjacentCount = 0;
}

int TreeNode::getVertexIndex() {
    return this->vertexIndex;
}

int TreeNode::getAdjacentCount() {
    return this->adjacentCount;
}
