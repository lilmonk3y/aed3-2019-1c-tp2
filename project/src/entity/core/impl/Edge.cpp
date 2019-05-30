//
// Created by Christian nahuel Rivera on 12/5/19.
//

#include "../Edge.h"

int Edge::getLeftVertex() const {
    return this->lVectexIndex;
}

int Edge::getRigthVertex() const {
    return this->rVertexIndex;
}

long Edge::getEdgeCost() const {
    return this->edgeCost;
}

Edge::Edge(int vertex1, int vertex2, long cost) {
    this->rVertexIndex = vertex1;
    this->lVectexIndex = vertex2;
    this->edgeCost = cost;
}

/*bool Edge::operator==(const Edge *other)const {
    return (this->lVectexIndex == other->getLeftVertex() && this->rVertexIndex == other->getRigthVertex() && this->componentIndex == other->getEdgeCost())
        || (this->lVectexIndex == other->getRigthVertex() && this->rVertexIndex == other->getLeftVertex() && this->componentIndex == other->getEdgeCost());
}

bool Edge::operator<(const Edge &other)const {
    return this->componentIndex < other.getEdgeCost();
}*/


bool operator==(const Edge first, const Edge other) {
    return (first.getLeftVertex() == other.getLeftVertex() && first.getRigthVertex() == other.getRigthVertex()/* && first.getEdgeCost() == other.getEdgeCost()*/)
    || (first.getLeftVertex() == other.getRigthVertex() && first.getRigthVertex()== other.getLeftVertex() /*&& first.getEdgeCost()== other.getEdgeCost()*/);
}

bool operator<(const Edge first, const Edge other) { // ES UN MENOR IGUAL
    if(first.getEdgeCost() == other.getEdgeCost()) { // ES UN MENOR IGUAL, sino el iterador de set quita los ejes de igual peso
        return true;
    }
    return first.getEdgeCost() < other.getEdgeCost();
}
