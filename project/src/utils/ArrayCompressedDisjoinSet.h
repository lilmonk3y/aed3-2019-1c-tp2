//
// Created by Christian nahuel Rivera on 12/5/19.
//

#ifndef AED3_2019_1C_TP2_COMPRESSEDDISJOINSET_H
#define AED3_2019_1C_TP2_COMPRESSEDDISJOINSET_H


#include "DisjoinSet.h"
#include <vector>

class ArrayCompressedDisjoinSet : public DisjoinSet {
public:
    int find(int vertex);
    void join(int alreadyIn, int newNode);
    void create(Graph *graph);
    std::set<int>* getSet(int vertexIndex);

private:
    std::vector<int> components;
    std::vector<int> heights;
    std::vector<std::set<int>*>* sets;
};
#endif //AED3_2019_1C_TP2_COMPRESSEDDISJOINSET_H
