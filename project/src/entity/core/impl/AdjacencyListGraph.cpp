//
// Created by Christian nahuel Rivera on 12/5/19.
//

#include "../AdjacencyListGraph.h"

AdjacencyListGraph::AdjacencyListGraph(int vertexAmount) {
    this->resetSize(vertexAmount);
    this->edges = new set<Edge>();
    this->maxWeight = 0; // es de tipo long
}

// crea el tamaño de vertices para luego agregarle las adyacencias
void AdjacencyListGraph::resetSize(int newVerticesSize) {
    this->graphSize = newVerticesSize;
}

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
/*
 *  O(1) amortizado + O(1) amortizado, sino log(n)
 */
void AdjacencyListGraph::addEdge(int vertexIndex1, int vertexIndex2, long edgeCost) {
    if(this->vertexAdjacents.find(vertexIndex1) == this->vertexAdjacents.end()){
        this->vertexAdjacents.insert(std::pair<int,std::list<AdjacencyNode*>>(vertexIndex1,std::list<AdjacencyNode*>()));
    }
    this->vertexAdjacents.at(vertexIndex1).push_back(new AdjacencyNode(vertexIndex2, edgeCost));

    if(this->vertexAdjacents.find(vertexIndex2) == this->vertexAdjacents.end()){
        this->vertexAdjacents.insert(std::pair<int,std::list<AdjacencyNode*>>(vertexIndex2,std::list<AdjacencyNode*>()));
    }
    this->vertexAdjacents.at(vertexIndex2).push_back(new AdjacencyNode(vertexIndex1, edgeCost));

    Edge edge(vertexIndex1,vertexIndex2,edgeCost); //O(1)
    this->edges->insert(edge);

    if(edgeCost > this->maxWeight) { // actualizo el peso maximo
        this->maxWeight = edgeCost;
    }
}

// esto sirve para obtener la cantidad de ejes
int AdjacencyListGraph::getVertexSize() {
    return this->graphSize;
}

/*
 * Retornar el conjunto de ejes en O(1)
 */
set<Edge>* AdjacencyListGraph::getEdgeSet() {
    return this->edges;
}

//// vector de ejes
//std::vector<Edge> *AdjacencyListGraph::getEdges() {
//    std::vector<Edge> *edges = new std::vector<Edge>();
//    for(auto vertex : this->vertexAdjacents){
//        for(auto adyacent : vertex.second){
//            Edge edge = Edge(vertex.first,adyacent->getVertex(),adyacent->getEdgeCost());
//            if(! this->alreadyInserted(edges, &edge)){
//                edges->push_back(edge);
//            }
//        }
//    }
//    return edges;
//}

long AdjacencyListGraph::getTotalCost() { // solo usado en test, pero puede ser O(1) si lo guardamos en un campo
    std::set<Edge> *edges = this->getEdgeSet();
    long totalCost = 0;
    for (auto edge : *edges) {
        totalCost += edge.getEdgeCost();
    }
    return totalCost;
}

//bool AdjacencyListGraph::alreadyInserted(std::vector<Edge> *edges, Edge *edge) { // puede tener costo O(log n) con el getEdgeSet
//    for(auto inEdge : *edges){
//        if(inEdge == *edge){
//            return true;
//        }
//    }
//    return false;
//}

AdjacencyListGraph::~AdjacencyListGraph() {
    for (const auto& adjacencyList : vertexAdjacents) {
        for (auto* node : adjacencyList.second) {
            delete node;
        }
    }
    delete edges; // podría haber sido borrado porque está expuesto en la función getEdgeSet sin
                  // const-modifiers y en ese caso generaría acá un double delete, pero para
                  // no modificar tanto asumo que no fue borrado
}


/// metodos nuevos que agregó axel:
long AdjacencyListGraph::getMaxWeight() {
    return this->maxWeight;
}

set<int> AdjacencyListGraph::getNeighbors(int indiceVertice) { // costo O(n)
    set<int> neighbors;
    list<AdjacencyNode*> adyacentes = vertexAdjacents.at(indiceVertice);// adyacentes del indice actual
    for(const auto& iter : adyacentes) { // itero los adyacentes
        int indexFromNeighborVertex = iter->getVertex(); // vertice adyacente
        neighbors.insert(indexFromNeighborVertex);
    }
    return neighbors;
}

std::list<AdjacencyNode *> *AdjacencyListGraph::getAdyacents(int vertexIndex) {
    return &(this->vertexAdjacents.at(vertexIndex));
}
