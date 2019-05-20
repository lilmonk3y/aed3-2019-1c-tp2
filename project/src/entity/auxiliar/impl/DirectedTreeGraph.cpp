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
    TreeNode *newFather = this->getIndex(fatherIndex);
    makeMyRootMySon(this->vertices.at(sonIndex), newFather);

    this->vertices.at(sonIndex)->setFather(newFather, newFather->getComponentIndex());

    updateMySonsComponent(sonIndex, this->getIndex(fatherIndex)->getComponentIndex());
}

void DirectedTreeGraph::updateMySonsComponent(int sonIndex, int component) const {// Update the child of son in the new component
    for(auto vertex : vertices){
        if(vertex->getFather() == vertices.at(sonIndex) && vertices.at(sonIndex) != vertex){
            vertex->setComponentIndex(component);
            updateMySonsComponent(vertex->getVertexIndex(), component);
        }
    }
}

TreeNode *DirectedTreeGraph::getIndex(int index) {
    return this->vertices.at(index);
}

void DirectedTreeGraph::makeMyRootMySon(TreeNode *node, TreeNode *newFather) {
    if(node->getFather() != nullptr){
        TreeNode* grandFather = getRoot(node->getFather());
        if(grandFather != newFather)
            grandFather->setFather(node, node->getComponentIndex());
    }
}

TreeNode *DirectedTreeGraph::getRoot(TreeNode *node) {
    if(node->getFather() == nullptr){
        return node;
    }else{
        return getRoot(node->getFather());
    }
}
