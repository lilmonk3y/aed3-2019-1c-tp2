//
// Created by Christian nahuel Rivera on 15/5/19.
//

#ifndef AED3_2019_1C_TP2_REPRESENTATION_H
#define AED3_2019_1C_TP2_REPRESENTATION_H

#include "RepresentationNode.h"
#include <vector>

class Representation{
public:
    virtual void create(int size) = 0;
    virtual void setAtIndex(int index, int value) = 0;
    virtual int getSize() = 0;
    virtual std::vector<RepresentationNode> getAllVertex() = 0;
    virtual int getIndex(int index) = 0;
};
#endif //AED3_2019_1C_TP2_REPRESENTATION_H
