//
// Created by Christian nahuel Rivera on 12/5/19.
//

#ifndef AED3_2019_1C_TP2_EDGE_H
#define AED3_2019_1C_TP2_EDGE_H

class Edge{
public:
    Edge(int vertex1,int vertex2,long cost);
    int getLeftVertex();
    int getRigthVertex();
    long getEdgeCost();
    bool operator==(Edge other);

private:
    int lVectexIndex;
    int rVertexIndex;
    long edgeCost;
};

struct
{
    bool operator() (Edge& lEdge, Edge& rEdge) {
        return lEdge.getEdgeCost() < rEdge.getEdgeCost();
    }
} cmpWeigth ;

#endif //AED3_2019_1C_TP2_EDGE_H
