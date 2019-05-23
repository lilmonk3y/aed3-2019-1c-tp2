//
// Created by Axel Arrondo on 2019-05-23.
//

#include "SegmentationAlgorithm.h"

DisjoinSet* SegmentationAlgorithm::segmentateGraphImage(Graph *graph) {
    Graph* Imagegraph = new AdjacencyListGraph(graph->getVertex());
    DisjoinSet* disjoinSet;
    disjoinSet->create(graph); // crear lista de conjuntos disjunto del grafo
    std::vector<Edge> *edges = graph->getEdges(); // obtener E de G=(V,E)
    sort(edges->begin(),edges->end()); // ordenar con merge sort, de manera no-decreciente la lista de todos los ejes
    for(auto edge : *edges){
        int componentI = disjoinSet->find(edge.getLeftVertex()); // busco componente vertice i, extremo del eje
        int componentJ = disjoinSet->find(edge.getRigthVertex());// busco componente vertice j, extremo del eje
        if( componentI !=  componentJ ) {
            if( edge.getEdgeCost() <= minInternalDifference(componentI,componentJ) ) {
                disjoinSet->join(componentI, componentJ); // union componentes a las cuales pertenece los vertices
            }
        }
    }
    return disjoinSet;
}

int SegmentationAlgorithm::minInternalDifference(int componentI, int componentJ) {
    int difCompI = internalDifference(componentI)+tau(componentI);
    int difCompJ = internalDifference(componentJ)+tau(componentJ));
    if (difCompI < difCompJ){
        return difCompI;
    }
    return difCompJ;
}


int SegmentationAlgorithm::internalDifference(int component) {
    return max(conjuntoDeLosPesos(getMST(component)));
}

// implementar max(conjuntoDeLosPesos, eso solo

int SegmentationAlgorithm::tau(int component) {
    int k = 2; // eso se setea a mano
    return k/cardinal(component);
}

int SegmentationAlgorithm::cardinal(DisjoinSet* disjoinSet, Graph* Imagegraph, int component) {
    int quantityVertex = Imagegraph->getVertex();
    //for(auto edge : *edges){

    //}
}
