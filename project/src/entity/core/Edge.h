//
// Created by Christian nahuel Rivera on 12/5/19.
//

#ifndef AED3_2019_1C_TP2_EDGE_H
#define AED3_2019_1C_TP2_EDGE_H

#include <algorithm>

class Edge{
public:
    Edge(int vertex1,int vertex2,long cost);
    int getLeftVertex() const;
    int getRigthVertex() const;
    long getEdgeCost() const;
    //bool operator==(const Edge *other)const;
    //bool operator<(const Edge &other)const;

private:
    int lVectexIndex;
    int rVertexIndex;
    long edgeCost;
};

bool operator==(const Edge first, const Edge other);
bool operator<(const Edge first, const Edge other); // ES UN MENOR IGUAL EN REALIDAD
bool edgeComparatorByCost(const Edge first, const Edge second);

/*
struct
{
    bool operator() (Edge& lEdge, Edge& rEdge) {
        return lEdge.getEdgeCost() < rEdge.getEdgeCost();
    }
} cmpWeigth ;
*/

#endif //AED3_2019_1C_TP2_EDGE_H
