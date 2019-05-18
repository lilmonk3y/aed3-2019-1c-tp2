//
// Created by Christian nahuel Rivera on 12/5/19.
//

#include "../AdjacencyNode.h"

AdjacencyNode::AdjacencyNode(int vertexIndex, long edgeCost) {
    this->vertexIndex = vertexIndex;
    this->edgeCost = edgeCost;
}

int AdjacencyNode::getVertex() {
    return this->vertexIndex;
}

long AdjacencyNode::getEdgeCost() {
    return this->edgeCost;
}
