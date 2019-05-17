//
// Created by Christian nahuel Rivera on 17/5/19.
//

#include "TreeRepresentation.h"

void TreeRepresentation::create(int size) {
    this->representation = new DirectedTreeGraph(size);

}

int TreeRepresentation::getIndex(int index) {
    return this->representation->getIndex(index);
}

