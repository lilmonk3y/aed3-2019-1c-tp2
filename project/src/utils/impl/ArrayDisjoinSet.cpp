//
// Created by Christian nahuel Rivera on 12/5/19.
//
#include "../ArrayDisjoinSet.h" 

void ArrayDisjoinSet::create(Graph *graph) {
    std::vector<int> components;
    components.resize(graph->getVertex());
    for(std::size_t index = 0; index < components.size(); index++){
        components.at(index) = index;
    }
    this->components = components;

    std::vector<std::set<int>*>* diccSetsInstance = new std::vector<std::set<int>*>();
    diccSetsInstance->resize(graph->getVertex());// O(n)
    for(std::size_t index = 0; index < diccSetsInstance->size(); index++){
        std::set<int>* setsInstance = new std::set<int>();
        setsInstance->insert(index);
        diccSetsInstance->at(index) = setsInstance;
    }
    this->sets = diccSetsInstance;
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

    std::set<int>* alreadyInSet = this->getSet(alreadyIn);// O(1)
    std::set<int>* newNodeSet = this->getSet(newNode);// O(1)
    unionSetLeft(alreadyInSet,newNodeSet); // o(n) de los conjuntos
    this->sets->at(alreadyIn) = alreadyInSet;// o(1)
    this->sets->at(newNode) = NULL;// conjunto vacio

}

void ArrayDisjoinSet::unionSetLeft(std::set<int>* aSet ,std::set<int>* bSet) { // O(n), itero elementos de bSet
    for(auto element: *bSet) {
        aSet->insert(element);
    }
}

std::set<int>* ArrayDisjoinSet::getSet(int indexComponent) {
    return this->sets->at(indexComponent);
}