//
// Created by Christian nahuel Rivera on 18/5/19.
//

#include "../TreeCompressedDisjoinSet.h"

void TreeCompressedDisjoinSet::create(Graph *graph) {
    this->components= new DirectedTreeGraph(graph->getVertex());

    std::vector<int> heights;
    heights.resize(graph->getVertex());
    for(int index = 0; index < graph->getVertex(); index++){
        heights.at(index) = 1;
    }
    this->heights = heights;
}

int TreeCompressedDisjoinSet::find(int vertex) {
    if( this->components->getIndex(vertex)->getComponentIndex() != vertex){
        this->components->getIndex(vertex)->setComponentIndex(find(this->components->getIndex(vertex)->getComponentIndex()));
    }
    return this->components->getIndex(vertex)->getComponentIndex();
}

void TreeCompressedDisjoinSet::join(int alreadyIn, int newNode) {
    int lRepresentative = find(alreadyIn);
    int rRepresentative = find(newNode);

    if(heights.at(lRepresentative) < heights.at(rRepresentative)){
        this->components->getIndex(lRepresentative)->setComponentIndex(rRepresentative);
    }else{
        this->components->getIndex(rRepresentative)->setComponentIndex(lRepresentative);
    }
    if(heights.at(lRepresentative) == heights.at(rRepresentative)) {
        this->heights.at(rRepresentative) = this->heights.at(rRepresentative) + 1;
    }
}