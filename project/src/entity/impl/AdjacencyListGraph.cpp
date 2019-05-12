//
// Created by Christian nahuel Rivera on 12/5/19.
//

#include "../AdjacencyListGraph.h"

bool AdjacencyListGraph::adjacent(int vertexIndex1, int vertexIndex2) {
    return isAdjacent(vertexIndex1, vertexIndex2) && isAdjacent(vertexIndex2, vertexIndex1);

}

bool AdjacencyListGraph::isAdjacent(int origin, int destiny) {
    bool response = false;
    for(auto iter = vertexAdjacents.at(origin).begin(); iter != vertexAdjacents.at(origin).end() ;iter ++){
        if((*iter)->getVertex() == destiny){
            response = true;
        }
    }
    return response;
}

AdjacencyListGraph::AdjacencyListGraph(int vertexAmount) {
    this->vertexAdjacents = std::vector<std::list<AdjacencyNode*>>(vertexAmount);
    for(int index = 0; index < this->vertexAdjacents.size(); index++){
        this->vertexAdjacents.at(index) = std::list<AdjacencyNode*>();
    }
}

void AdjacencyListGraph::addEdge(int vertexIndex1, int vertexIndex2, long edgeCost) {
    this->vertexAdjacents.at(vertexIndex1).push_back(new AdjacencyNode(vertexIndex2, edgeCost));
    this->vertexAdjacents.at(vertexIndex2).push_back(new AdjacencyNode(vertexIndex1, edgeCost));
}

int AdjacencyListGraph::getVertex() {
    return static_cast<int>(this->vertexAdjacents.size());
}
