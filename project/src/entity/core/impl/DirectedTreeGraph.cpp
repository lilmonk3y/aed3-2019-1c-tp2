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
        this->vertices.emplace_back(TreeNode(index));
    }
}

int DirectedTreeGraph::getVertex() {
    return static_cast<int>(this->vertices.size());
}

bool DirectedTreeGraph::adjacent(int vertexIndex1, int vertexIndex2) {
    std::vector<TreeEdge> vertex1Adyacents = this->vertices.at(vertexIndex1).getAdyacentNodes();
    for (auto &vertex1Adyacent : vertex1Adyacents) {
        if(vertex1Adyacent.getParent() == vertexIndex2){
            return true;
        }
    }
    return false;
}

void DirectedTreeGraph::addEdge(int vertexIndex1, int vertexIndex2, long edgeCost) {
    this->vertices.at(vertexIndex1).addAdjacent(TreeNode(this->vertices.at(vertexIndex2)), edgeCost);
}

std::vector<Edge> *DirectedTreeGraph::getEdges() {
    auto *edges = new std::vector<Edge>();
    for(auto treeNode = this->vertices.begin(); treeNode != this->vertices.end(); treeNode++){
        for(int adjacentIndex = 0; adjacentIndex < treeNode.base()->getAdjacentCount(); adjacentIndex++){
            Edge edge = Edge((*treeNode).getVertexIndex(),treeNode.base()->getAdyacentNodes().at(adjacentIndex).getParent(),treeNode.base()->getAdyacentNodes().at(adjacentIndex).getCost());
            if(! this->alreadyInserted(edges,&edge)){
                edges->emplace_back(edge);
            }
        }
    }
    return edges;
}

long DirectedTreeGraph::getTotalCost() {
    long totalCosts = 0;
    auto edges = this->getEdges();
    for(auto edge = edges->begin();edge != edges->end(); edge++){
        totalCosts += (*edge).getEdgeCost();
    }
    return totalCosts;
}

bool DirectedTreeGraph::alreadyInserted(std::vector<Edge> *edges, Edge *edge) {
    for(auto inEdge : *edges){
        if(inEdge == *edge){
            return true;
        }
    }
    return false;
}

int DirectedTreeGraph::getIndex(int index) {
    return this->vertices.at(index).getVertexIndex();
}
