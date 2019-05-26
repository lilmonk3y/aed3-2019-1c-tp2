//
// Created by Axel Arrondo on 2019-05-23.
//

#include "SegmentationAlgorithm.h"
#include <set>

DisjoinSet& SegmentationAlgorithm::graphSementationIntoSets(AdjacencyListGraph& graph) {
    AdjacencyListGraph* grafo = new AdjacencyListGraph(graph.getVertex());
    DisjoinSet* disjoinSet;
    disjoinSet->create(&graph); // crear lista de conjuntos disjunto del grafo
    std::vector<Edge>* edges = graph.getEdges(); // obtener E de G=(V,E)
    sort(edges->begin(),edges->end()); // ordenar con merge sort, de manera no-decreciente la lista de todos los ejes
    for(auto edge : *edges){
        int indiceComponenteI = disjoinSet->find(edge.getLeftVertex()); // busco componente vertice i, extremo del eje
        int indicecomponenteJ = disjoinSet->find(edge.getRigthVertex());// busco componente vertice j, extremo del eje
        if( indiceComponenteI !=  indicecomponenteJ ) {
            if( edge.getEdgeCost() <= minInternalDifference(disjoinSet,grafo,indiceComponenteI,indicecomponenteJ) ) {
                disjoinSet->join(indiceComponenteI, indicecomponenteJ); // union componentes a las cuales pertenece los vertices
            }
        }
    }
    return *disjoinSet;
}

int SegmentationAlgorithm::minInternalDifference(DisjoinSet* disjoinSet,AdjacencyListGraph* grafo,int componenteI, int componenteJ) {
    int difCompI = internalDifference(disjoinSet,componenteI,grafo) + tau(disjoinSet, grafo, componenteI) ;
    int difCompJ = internalDifference(disjoinSet,componenteJ,grafo) + tau(disjoinSet, grafo, componenteJ) ;
    return min(difCompI , difCompJ);
}

// implementar max(conjuntoDeLosPesos, eso solo
int SegmentationAlgorithm::internalDifference(DisjoinSet* disjoinSet,int indiceDeComponente,AdjacencyListGraph* grafo) {
    set<int> componente = construirComponente(disjoinSet,indiceDeComponente,grafo); // ok

    Graph* subGrafoComponente = AdjacencyListGraph::adjacencyListInducedSubGraph(grafo,componente);// G=(C,E)

    GetMST kruskal = GetMST(new ArrayDisjoinSet());// elijo la estrategia del disjoint set
    Graph* arbolRecubridorMinimoDeLaComponente = kruskal.getMST(subGrafoComponente); // type AdjacencyListGraph

    return pesoMaximo(arbolRecubridorMinimoDeLaComponente);
}

// esto lo deberia hacer el disjoint set, reconstruir un conjunto disjunto
// queda desprolijo el imageGraph
// esto esta bien implementado:
set<int> SegmentationAlgorithm::construirComponente(DisjoinSet* disjoinSet, int indiceDeComponente, AdjacencyListGraph* Imagegraph) {
    std::set<int>  componenteVertices;
    int quantityVertex = Imagegraph->getVertex(); // cantidad de vertices
    for(int indexVertex=1; indexVertex <= quantityVertex; indexVertex++) {
        if  (disjoinSet->find(indexVertex) == indiceDeComponente) {
            componenteVertices.insert(indexVertex);
        }
    }
    return componenteVertices;
}

int SegmentationAlgorithm::tau(DisjoinSet* disjoinSet,AdjacencyListGraph* Imagegraph, int component) {
    int k = 2; // eso se setea a mano
    return k/cardinal(disjoinSet,Imagegraph,component);
}

// no deberia implementarse esto aca, sino dentro del disjoint set
// Graph se usa solo para el cardinal de vertices
int SegmentationAlgorithm::cardinal(DisjoinSet* disjoinSet,AdjacencyListGraph* Imagegraph, int component) {
    int quantityVertex = Imagegraph->getVertex();
    int cardinal = 0;
    for(int indexVertex=1; indexVertex<=quantityVertex; indexVertex++) {
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

int SegmentationAlgorithm::pesoMaximo(Graph* graph) {
    int pesoMaximo = 0;
    vector<Edge>* ejes = graph->getEdges();
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
