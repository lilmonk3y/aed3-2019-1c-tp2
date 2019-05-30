//
// Created by Christian nahuel Rivera on 12/5/19.
//

#ifndef AED3_2019_1C_TP2_DEFAULTDISJOINSET_H
#define AED3_2019_1C_TP2_DEFAULTDISJOINSET_H

#include "DisjoinSet.h"
#include <vector>

class ArrayDisjoinSet : public DisjoinSet {
public:
    int find(int vertex);
    void join(int alreadyIn, int newNode);
    void create(Graph *graph);
    std::set<int>* getSet(int indexComponent);

protected:
    std::vector<int> components;
    std::vector<std::set<int>*>* sets;
    void unionSetLeft(std::set<int>* aSet ,std::set<int>* bSet);
};
#endif //AED3_2019_1C_TP2_DEFAULTDISJOINSET_H
