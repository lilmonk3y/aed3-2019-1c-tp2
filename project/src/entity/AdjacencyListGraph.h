//
// Created by Christian nahuel Rivera on 12/5/19.
//

#include <vector>
#include <list>
#include "Graph.h"
#include "AdjacencyNode.h"

class AdjacencyListGraph : public Graph{
public:
    AdjacencyListGraph(int vertexAmount);
    int getVertex();
    bool adjacent(int vertexIndex1, int vertexIndex2);
    void addEdge(int vertexIndex1, int vertexIndex2, long edgeCost);

private:
    std::vector<std::list<AdjacencyNode*>> vertexAdjacents;

    bool isAdjacent(int origin, int destiny) ;
};