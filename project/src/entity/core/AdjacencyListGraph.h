//
// Created by Christian nahuel Rivera on 12/5/19.
//

#include <list>
#include "Graph.h"
#include "../auxiliar/AdjacencyNode.h"
#include <set>
#include <map>

using namespace std;

class AdjacencyListGraph : public Graph{
public:
    AdjacencyListGraph(int vertexAmount);
    int getVertexSize();
    bool adjacent(int vertexIndex1, int vertexIndex2);
    void addEdge(int vertexIndex1, int vertexIndex2, long edgeCost);
    set<Edge>* getEdgeSet();// O(1) (conjunto ordenado creciente al iterar)
    long getTotalCost();
    void resetSize(int newVerticesSize);
    set<int> getNeighbors(int indiceVertice);// metodo nuevo
    long getMaxWeight(); // O(1), retorna el peso de la arista, cuyo peso es el mayor de todos
    ~AdjacencyListGraph();
    std::list<AdjacencyNode*>* getAdyacents(int vertexIndex);

private:
    std::map<int, std::list<AdjacencyNode*>> vertexAdjacents;
    set<Edge>* edges;// insersion en O(1) amortizado (el set no precisa comprobacion si ya fue ingresado)
    long maxWeight;
    int graphSize;

    bool isAdjacent(int origin, int destiny) ;
};