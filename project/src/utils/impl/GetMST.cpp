//
// Created by Christian nahuel Rivera on 12/5/19.
//
#include "../GetMST.h"
#include "../../entity/core/AdjacencyListGraph.h"

GetMST::GetMST(DisjoinSet *disjoinSetStrategy) {
    this->disjoinSet = disjoinSetStrategy;

}

Graph * GetMST::getMST(Graph *graph) {
    Graph *mst = new AdjacencyListGraph(graph->getVertex());
    disjoinSet->create(graph, nullptr);
    std::vector<Edge> *edges = graph->getEdges();
    sort(edges->begin(),edges->end());
    for(auto edge : *edges){
        if(disjoinSet->find(edge.getLeftVertex()) !=  disjoinSet->find(edge.getRigthVertex())){
            mst->addEdge(edge.getLeftVertex(),edge.getRigthVertex(),edge.getEdgeCost());
            disjoinSet->join(disjoinSet->find(edge.getLeftVertex()), disjoinSet->find(edge.getRigthVertex()));
        }
    }
    return mst;
}
