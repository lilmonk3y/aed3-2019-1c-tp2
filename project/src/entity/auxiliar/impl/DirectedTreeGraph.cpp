//
// Created by Christian nahuel Rivera on 15/5/19.
//

#include "../DirectedTreeGraph.h"

DirectedTreeGraph::DirectedTreeGraph(int vertexSize) {
    this->resetSize(vertexSize);
}

void DirectedTreeGraph::resetSize(int newVerticesSize) {
    this->vertices.clear();
    for(int index = 0; index < newVerticesSize; index++){
        this->vertices.emplace_back(new TreeNode(index));
    }
}

int DirectedTreeGraph::getVertex() {
    return static_cast<int>(this->vertices.size());
}

void DirectedTreeGraph::addToComponent(int fatherIndex, int sonIndex) {
    this->vertices.at(sonIndex)->setFather(this->getIndex(fatherIndex), this->getIndex(fatherIndex)->getComponentIndex());

    updateMySonsComponent(sonIndex);

}

void DirectedTreeGraph::updateMySonsComponent(int sonIndex) const {// Update the child of son in the new component
    for(auto vertex : vertices){
        if(vertex->getFather() == vertices.at(sonIndex)){
            vertex->setComponentIndex(vertices.at(sonIndex)->getComponentIndex());
            updateMySonsComponent(vertex->getVertexIndex());
        }
    }
}

TreeNode *DirectedTreeGraph::getIndex(int index) {
    return this->vertices.at(index);
}
