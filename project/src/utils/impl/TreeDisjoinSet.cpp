//
// Created by Christian nahuel Rivera on 17/5/19.
//

#include "../TreeDisjoinSet.h"

void TreeDisjoinSet::create(Graph *graph) {
    this->components = new DirectedTreeGraph(graph->getVertex());

    // conjuntos asociados a un vertice
    std::vector<std::set<int>*>* diccSetsInstance = new std::vector<std::set<int>*>();
    diccSetsInstance->resize(graph->getVertex());// O(n)
    for(std::size_t index = 0; index < diccSetsInstance->size(); index++){
        std::set<int>* setsInstance = new std::set<int>();
        setsInstance->insert(index);
        diccSetsInstance->at(index) = setsInstance;
    }
    this->sets = diccSetsInstance;
}

int TreeDisjoinSet::find(int vertex) {
    return this->components->getIndex(vertex)->getComponentIndex();
}

void TreeDisjoinSet::join(int alreadyIn, int newNode) { // creo que log(n)
    this->components->addToComponent(alreadyIn, newNode);

    std::set<int>* alreadyInSet = this->getSet(alreadyIn);// O(1)
    std::set<int>* newNodeSet = this->getSet(newNode);// O(1)
    unionSetLeft(alreadyInSet,newNodeSet); // o(n) de los conjuntos
    this->sets->at(alreadyIn) = alreadyInSet;// o(1)
    this->sets->at(newNode) = NULL;// conjunto vacio
}

void TreeDisjoinSet::unionSetLeft(std::set<int>* aSet ,std::set<int>* bSet) { // O(n), itero elementos de bSet
    for(auto element: *bSet) {
        aSet->insert(element);
    }
}


std::set<int>* TreeDisjoinSet::getSet(int indexComponent) {
    return this->sets->at(indexComponent);
}