//
// Created by Axel Arrondo on 2019-05-23.
//

#include "SegmentationAlgorithm.h"
#include <set>
#include <iostream>

SegmentationAlgorithm::SegmentationAlgorithm(AdjacencyListGraph* graph) {
   this->grafo = graph;
}


DisjoinSet* SegmentationAlgorithm::graphSementationIntoSets() {
    DisjoinSet* disjoinSet = new ArrayDisjoinSet();
    disjoinSet->create(grafo); // crear lista de conjuntos disjunto del grafo original

    vector<Edge>* edges = grafo->getEdges(); // obtener E de G=(V,E)
    sort(edges->begin(),edges->end()); // ordenar con merge sort, de manera no-decreciente la lista de todos los ejes
    for(vector <Edge> :: iterator edge = edges->begin(); edge != edges->end(); ++edge) {// itero todos los ejes.
        int indiceComponenteI = disjoinSet->find(edge->getLeftVertex()); // busco componente vertice i, extremo del eje
        int indicecomponenteJ = disjoinSet->find(edge->getRigthVertex());// busco componente vertice j, extremo del eje

        if( indiceComponenteI !=  indicecomponenteJ ) {
            if( edge->getEdgeCost() <= minInternalDifference(disjoinSet,indiceComponenteI,indicecomponenteJ) ) {
                disjoinSet->join(indiceComponenteI, indicecomponenteJ); // union componentes a las cuales pertenece los vertices
            }
        }
    }
    return disjoinSet;
}

int SegmentationAlgorithm::minInternalDifference(DisjoinSet* disjoinSet,int componenteI, int componenteJ) {
    int difCompI = internalDifference(disjoinSet,componenteI) + tau(disjoinSet, componenteI) ;
    int difCompJ = internalDifference(disjoinSet,componenteJ) + tau(disjoinSet, componenteJ) ;
    return min(difCompI , difCompJ);
}

// implementar max(conjuntoDeLosPesos, eso solo
int SegmentationAlgorithm::internalDifference(DisjoinSet* disjoinSet,int indiceDeComponente) {
    set<int> componente = construirComponente(disjoinSet,indiceDeComponente);

    Graph* subGrafoComponente = AdjacencyListGraph::adjacencyListInducedSubGraph(this->grafo,componente);// G=(C,E)
    GetMST kruskal = GetMST(new ArrayDisjoinSet());// elijo la estrategia del disjoint set
    Graph* arbolRecubridorMinimoDeLaComponente = kruskal.getMST(subGrafoComponente); // type AdjacencyListGraph

    return pesoMaximo(arbolRecubridorMinimoDeLaComponente);
}

// esto lo deberia hacer el disjoint set, reconstruir un conjunto disjunto
// queda desprolijo el imageGraph
// esto esta bien implementado:
set<int> SegmentationAlgorithm::construirComponente(DisjoinSet* disjoinSet, int indiceDeComponente) {
    std::set<int>  componenteVertices;
    int quantityVertex = this->grafo->getVertex(); // cantidad de vertices
    for(int indexVertex=0; indexVertex < quantityVertex; indexVertex++) {
        if  (disjoinSet->find(indexVertex) == indiceDeComponente) {
            componenteVertices.insert(indexVertex);
        }
    }
    return componenteVertices;
}

int SegmentationAlgorithm::tau(DisjoinSet* disjoinSet, int component) {
    int k = 2; // eso se setea a mano
    return k/cardinal(disjoinSet,component);
}

// no deberia implementarse esto aca, sino dentro del disjoint set
// Graph se usa solo para el cardinal de vertices
int SegmentationAlgorithm::cardinal(DisjoinSet* disjoinSet,int component) {
    int quantityVertex = this->grafo->getVertex();
    int cardinal = 0;
    for(int indexVertex=0; indexVertex<quantityVertex; indexVertex++) {
        if  (disjoinSet->find(indexVertex) == component) {
            cardinal = cardinal +1;
        }
    }
    return cardinal;
}

int SegmentationAlgorithm::min(int a ,int b) {
    if(a<b){
        return a;
    }
    return b;
}

int SegmentationAlgorithm::pesoMaximo(Graph* subgrafo) {
    int pesoMaximo = 0;
    vector<Edge>* ejes = subgrafo->getEdges();
    for(auto eje : *ejes) {
        if( pesoMaximo < eje.getEdgeCost() ) {
            pesoMaximo = eje.getEdgeCost();
        }
    }
    return pesoMaximo;
}

/*
Graph& imageToGraph(vector<vector<int> >& imagen) {
    for(auto pixel:imagen) {

    }
}*/
