//
// Created by Christian nahuel Rivera on 12/5/19.
//
#include "../GetMST.h"
#include "../../entity/core/AdjacencyListGraph.h"
#include <algorithm>
#include <iostream>

GetMST::GetMST(DisjoinSet *disjoinSetStrategy) {
    this->disjoinSet = disjoinSetStrategy;

}

Graph * GetMST::getMST(Graph *graph) { // O(#ejes.costo del join del disjoint set)
    Graph *mst = new AdjacencyListGraph(graph->getVertex());
    disjoinSet->create(graph);
    set<Edge>* edges = graph->getEdgeSet(); // O(1) (elementos ordenados creciente)

    //sort(edges->begin(),edges->end()); // INNECESARIO PORQUE EL SET YA VIENE ORDENADO AL ITERAR CRECIENTE

    // los ejes ESTAN ordenados de manera creciente, sino no funciona el algoritmo:
    for(auto edge : *edges){ // O(#ejes)
        if(disjoinSet->find(edge.getLeftVertex()) !=  disjoinSet->find(edge.getRigthVertex())){ // O(1)
            mst->addEdge(edge.getLeftVertex(),edge.getRigthVertex(),edge.getEdgeCost());// O(1) amortizado
            disjoinSet->join(disjoinSet->find(edge.getLeftVertex()), disjoinSet->find(edge.getRigthVertex())); // depende del disjoint set usado
        }
    }
    return mst;
}