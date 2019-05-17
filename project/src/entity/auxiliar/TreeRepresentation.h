//
// Created by Christian nahuel Rivera on 17/5/19.
//

#ifndef AED3_2019_1C_TP2_TREEREPRESENTATION_H
#define AED3_2019_1C_TP2_TREEREPRESENTATION_H


#include "Representation.h"
#include "../core/DirectedTreeGraph.h"

class TreeRepresentation : public Representation {
public:
    void create(int size) override;
    int getIndex(int index);
private:
    DirectedTreeGraph * representation;
};


#endif //AED3_2019_1C_TP2_TREEREPRESENTATION_H
