//
// Created by Christian nahuel Rivera on 12/5/19.
//

#include <set>
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

std::vector<Edge> *AdjacencyListGraph::getEdges() {
    std::vector<Edge> *edges = new std::vector<Edge>();
    for(int vertex = 0; vertex < this->vertexAdjacents.size(); vertex++){
        for(auto iterator = this->vertexAdjacents.at(vertex).begin(); iterator != this->vertexAdjacents.at(vertex).end(); iterator++){
            Edge edge = Edge(vertex,(*iterator)->getVertex(),(*iterator)->getEdgeCost());
            if(! this->alreadyInserted(edges, &edge)){
                edges->push_back(edge);
            }
        }
    }
    return edges;
}

long AdjacencyListGraph::getTotalCost() {
    std::vector<Edge> *edges = this->getEdges();
    long totalCost = 0;
    for (auto edge : *edges) {
        totalCost += edge.getEdgeCost();
    }
    return totalCost;
}

bool AdjacencyListGraph::alreadyInserted(std::vector<Edge> *edges, Edge *edge) {
    for(auto inEdge : *edges){
        if(inEdge == *edge){
            return true;
        }
    }
    return false;
}
