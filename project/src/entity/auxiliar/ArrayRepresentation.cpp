//
// Created by Christian nahuel Rivera on 17/5/19.
//

#include "ArrayRepresentation.h"

void ArrayRepresentation::create(int size) {
    for(int index = 0; index < size; index++){
        this->representation.at(index) = index;
    }
}
