//
// Created by Christian nahuel Rivera on 15/5/19.
//

#include "../TreeEdge.h"

TreeEdge::TreeEdge(int parentIndex, long edgeCost) {
    this->edge = std::make_pair(parentIndex,edgeCost);
}

int TreeEdge::getParent() {
    return this->edge.first;
}

long TreeEdge::getCost() {
    return this->edge.second;
}
