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
    this->vertexAdjacents = std::vector<std::list<AdjacencyNode*>>(newVerticesSize);
    for(std::size_t index = 0; index < this->vertexAdjacents.size(); index++){
        this->vertexAdjacents.at(index) = std::list<AdjacencyNode*>();
    }
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

void AdjacencyListGraph::addEdge(int vertexIndex1, int vertexIndex2, long edgeCost) { // O(1) amortizado + O(1) amortizado, sino log(n)
    this->vertexAdjacents.at(vertexIndex1).push_back(new AdjacencyNode(vertexIndex2, edgeCost));// at:O(1), push_back: O(1) amortizado
    this->vertexAdjacents.at(vertexIndex2).push_back(new AdjacencyNode(vertexIndex1, edgeCost));
    Edge edge(vertexIndex1,vertexIndex2,edgeCost); //O(1)
    // en vez de un set podemos usar una lista y agregamos en O(1), pero hay que comprobar la pertenencia (suma costo):
    this->edges->insert(edge);// O(1) amortizado, no recibe punteros, sino el valor real

    if(edgeCost > this->maxWeight) { // actualizo el peso maximo
        this->maxWeight = edgeCost;
    }
}

// esto sirve para obtener la cantidad de ejes
int AdjacencyListGraph::getVertex() {
    return static_cast<int>(this->vertexAdjacents.size());
}

// retornar el conjunto de ejes en O(1)
set<Edge>* AdjacencyListGraph::getEdgeSet() {
    return this->edges;
}

// vector de ejes
std::vector<Edge> *AdjacencyListGraph::getEdges() {
    std::vector<Edge> *edges = new std::vector<Edge>();
    for(std::size_t vertex = 0; vertex < this->vertexAdjacents.size(); vertex++){
        for(auto iterator = this->vertexAdjacents.at(vertex).begin(); iterator != this->vertexAdjacents.at(vertex).end(); iterator++){
            Edge edge = Edge(vertex,(*iterator)->getVertex(),(*iterator)->getEdgeCost());
            if(! this->alreadyInserted(edges, &edge)){
                edges->push_back(edge);
            }
        }
    }
    return edges;
}

long AdjacencyListGraph::getTotalCost() { // solo usado en test, pero puede ser O(1) si lo guardamos en un campo
    std::vector<Edge> *edges = this->getEdges();
    long totalCost = 0;
    for (auto edge : *edges) {
        totalCost += edge.getEdgeCost();
    }
    return totalCost;
}

bool AdjacencyListGraph::alreadyInserted(std::vector<Edge> *edges, Edge *edge) { // puede tener costo O(log n) con el getEdgeSet
    for(auto inEdge : *edges){
        if(inEdge == *edge){
            return true;
        }
    }
    return false;
}

AdjacencyListGraph::~AdjacencyListGraph() {
    for (const auto& adjacencyList : vertexAdjacents) {
        for (auto* node : adjacencyList) {
            delete node;
        }
    }
}


/// metodos nuevos que agregó axel:

// para construir el subgrafo G'=(componente,E), donde G=(V,E) y componente incluido en V
AdjacencyListGraph* AdjacencyListGraph::adjacencyListInducedSubGraph(set<int> componente) {
    int cantidadVertices = this->getVertex(); // cantidad vertices V
    AdjacencyListGraph* subGraph = new AdjacencyListGraph(cantidadVertices);// O(n), estructura vacia subgrafo

    //vector<Edge> ejesG = *graph->getEdges(); // desrreferencio

    set<Edge> ejesG = *(this->getEdgeSet()); // desrreferencio
    for(const auto& iter : ejesG) { // O(M), ver si usar getNeighbors
        int iVertex = iter.getLeftVertex();
        int jVertex = iter.getRigthVertex();
        int pesoArista = iter.getEdgeCost();
        const bool i_vertex_is_in  = componente.find(iVertex) != componente.end();
        const bool j_vertex_is_in = componente.find(jVertex) != componente.end();

        // agregar solo ejes que inciden en los vertices de la componente:
        if(i_vertex_is_in &&  j_vertex_is_in) {
            subGraph->addEdge(iVertex,jVertex,pesoArista);
        }

    }
    return subGraph;
}

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