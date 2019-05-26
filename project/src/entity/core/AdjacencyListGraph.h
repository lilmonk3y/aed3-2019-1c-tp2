//
// Created by Christian nahuel Rivera on 12/5/19.
//

#include <list>
#include "Graph.h"
#include "../auxiliar/AdjacencyNode.h"
#include <set>

using namespace std;

class AdjacencyListGraph : public Graph{
public:
    AdjacencyListGraph(int vertexAmount);
    int getVertex();
    bool adjacent(int vertexIndex1, int vertexIndex2);
    void addEdge(int vertexIndex1, int vertexIndex2, long edgeCost);
    std::vector<Edge> *getEdges();
    long getTotalCost();
    void resetSize(int newVerticesSize);
    set<int> getNeighbors(int indiceVertice);// metodo nuevo
    static Graph* adjacencyListInducedSubGraph(Graph* graph,set<int> componente);// metodo nuevo
    ~AdjacencyListGraph();
private:
    std::vector<std::list<AdjacencyNode*>> vertexAdjacents;

    bool isAdjacent(int origin, int destiny) ;

    bool alreadyInserted(std::vector<Edge> *edges, Edge *edge);
};