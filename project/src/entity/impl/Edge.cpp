//
// Created by Christian nahuel Rivera on 12/5/19.
//

#include "../Edge.h"

int Edge::getLeftVertex() {
    return this->lVectexIndex;
}

int Edge::getRigthVertex() {
    return this->rVertexIndex;
}

long Edge::getEdgeCost() {
    return this->edgeCost;
}

Edge::Edge(int vertex1, int vertex2, long cost) {
    this->rVertexIndex = vertex1;
    this->lVectexIndex = vertex2;
    this->edgeCost = cost;
}

bool Edge::operator==(Edge other) {
    return (this->lVectexIndex == other.getLeftVertex() && this->rVertexIndex == other.getRigthVertex() && this->edgeCost == other.getEdgeCost())
        || (this->lVectexIndex == other.getRigthVertex() && this->rVertexIndex == other.getLeftVertex() && this->edgeCost == other.getEdgeCost());
}
