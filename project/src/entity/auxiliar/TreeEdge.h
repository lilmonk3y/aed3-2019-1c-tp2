//
// Created by Christian nahuel Rivera on 15/5/19.
//

#ifndef AED3_2019_1C_TP2_TREEEDGE_H
#define AED3_2019_1C_TP2_TREEEDGE_H


#include <utility>

class TreeEdge {
public:
    TreeEdge(int parentIndex, long edgeCost);
    int getParent();
    long getCost();
private:
    std::pair<int,long> edge;
};


#endif //AED3_2019_1C_TP2_TREEEDGE_H
