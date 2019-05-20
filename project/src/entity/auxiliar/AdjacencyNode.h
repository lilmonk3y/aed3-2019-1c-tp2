//
// Created by Christian nahuel Rivera on 12/5/19.
//

#ifndef AED3_2019_1C_TP2_NODE_H
#define AED3_2019_1C_TP2_NODE_H


class AdjacencyNode {
public:
    AdjacencyNode(int vertexIndex, long edgeCost);
    int getVertex();
    long getEdgeCost();
private:
    int vertexIndex;
    long edgeCost;
};


#endif //AED3_2019_1C_TP2_NODE_H
