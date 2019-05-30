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

    std::vector<std::set<int>*>* diccSetsInstance = new std::vector<std::set<int>*>();
    diccSetsInstance->resize(graph->getVertex());// O(n)
    for(std::size_t index = 0; index < diccSetsInstance->size(); index++){
        std::set<int>* setsInstance = new std::set<int>();
        setsInstance->insert(index);
        diccSetsInstance->at(index) = setsInstance;
    }
    this->sets = diccSetsInstance;
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

    std::set<int>* alreadyInSet = this->getSet(alreadyIn);// O(1)
    std::set<int>* newNodeSet = this->getSet(newNode);// O(1)
    unionSetLeft(alreadyInSet,newNodeSet); // o(n) de los conjuntos
    this->sets->at(alreadyIn) = alreadyInSet;// o(1)
    this->sets->at(newNode) = NULL;// conjunto vacio

}

void TreeCompressedDisjoinSet::unionSetLeft(std::set<int>* aSet ,std::set<int>* bSet) { // O(n), itero elementos de bSet
    for(auto element: *bSet) {
        aSet->insert(element);
    }
}



std::set<int>* TreeCompressedDisjoinSet::getSet(int indexComponent) {
    return this->sets->at(indexComponent);
}