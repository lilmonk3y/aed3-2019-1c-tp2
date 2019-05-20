//
// Created by Christian nahuel Rivera on 12/5/19.
//
#include "../DefaultDisjoinSet.h"

void DisjoinSetDefault::create(Graph *graph) {
    std::vector<int> components;
    components.resize(graph->getVertex());
    for(size_t index = 0; index < components.size(); index++){
        components.at(index) = index;
    }
    this->components = components;
}

int DisjoinSetDefault::find(int vertex) {
    return this->components.at(vertex);
}

void DisjoinSetDefault::join(int alreadyIn, int newNode) {
    int originalComponent = find(newNode);
    for (int &component : this->components) {
        if(component == originalComponent){
            component = find(alreadyIn);
        }
    }
}