//
// Created by Christian nahuel Rivera on 17/5/19.
//

#include "../TreeDisjoinSet.h"

void TreeDisjoinSet::create(Graph *graph) {
    if (components != NULL) delete components;
    this->components = new DirectedTreeGraph(graph->getVertexSize());
}

int TreeDisjoinSet::find(int vertex) {
    return this->components->getIndex(vertex)->getComponentIndex();
}

void TreeDisjoinSet::join(int alreadyIn, int newNode) {
    this->components->addToComponent(alreadyIn, newNode);
}

TreeDisjoinSet::~TreeDisjoinSet() {
    if (components != NULL) delete components;
}
