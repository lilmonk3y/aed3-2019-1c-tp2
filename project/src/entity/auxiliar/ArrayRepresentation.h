//
// Created by Christian nahuel Rivera on 17/5/19.
//

#ifndef AED3_2019_1C_TP2_ARRAYREPRESENTATION_H
#define AED3_2019_1C_TP2_ARRAYREPRESENTATION_H


#include "Representation.h"

class ArrayRepresentation : public Representation {
public:
    void create(int size);

private:
    std::vector<int> representation;
};


#endif //AED3_2019_1C_TP2_ARRAYREPRESENTATION_H
