//
// Created by Christian nahuel Rivera on 12/5/19.
//
#include "../ArrayDisjoinSet.h" 

void ArrayDisjoinSet::create(Graph *graph) {
    std::vector<int> components;
    components.resize(graph->getVertexSize());
    for(std::size_t index = 0; index < components.size(); index++){
        components.at(index) = index;
    }
    this->components = components;
}

int ArrayDisjoinSet::find(int vertex) {
    return this->components.at(vertex);
}

void ArrayDisjoinSet::join(int alreadyIn, int newNode) {
    int originalComponent = find(newNode);
    for (int &iter : this->components) {
        if(iter == originalComponent){
            iter = find(alreadyIn);
        }
    }
}