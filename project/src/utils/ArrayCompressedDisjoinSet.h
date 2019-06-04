//
// Created by Christian nahuel Rivera on 12/5/19.
//

#ifndef AED3_2019_1C_TP2_COMPRESSEDDISJOINSET_H
#define AED3_2019_1C_TP2_COMPRESSEDDISJOINSET_H


#include "DisjoinSet.h"
#include <vector>

class ArrayCompressedDisjoinSet : public DisjoinSet {
public:
    /*
     * complejidad O(ahpha(n)) que es una función casi constante
     */
    int find(int vertex);
    /*
     * complejidad O(ahpha(n)) que es una función casi constante
    */
    void join(int alreadyIn, int newNode);
    /*
     * O(n)
     */
    void create(Graph *graph);

private:
    std::vector<int> components;
    std::vector<int> heights;
};
#endif //AED3_2019_1C_TP2_COMPRESSEDDISJOINSET_H
