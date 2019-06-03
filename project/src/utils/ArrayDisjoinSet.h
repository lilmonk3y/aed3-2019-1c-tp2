//
// Created by Christian nahuel Rivera on 12/5/19.
//

#ifndef AED3_2019_1C_TP2_DEFAULTDISJOINSET_H
#define AED3_2019_1C_TP2_DEFAULTDISJOINSET_H

#include "DisjoinSet.h"
#include <vector>

class ArrayDisjoinSet : public DisjoinSet {
public:
    /*
     * complejidad O(1)
     */
    int find(int vertex);
    /*
     * complejidad O(n)
     */
    void join(int alreadyIn, int newNode);
    /*
     * complejidad O(n)
     */
    void create(Graph *graph);


protected:
    std::vector<int> components;
};
#endif //AED3_2019_1C_TP2_DEFAULTDISJOINSET_H
