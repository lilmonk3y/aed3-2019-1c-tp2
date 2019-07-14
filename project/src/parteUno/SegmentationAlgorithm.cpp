//
// Created by Axel Arrondo on 2019-05-23.
//

#include "SegmentationAlgorithm.h"
#include <set>
#include <iostream>
#include <fstream>
#include <algorithm>

SegmentationAlgorithm::SegmentationAlgorithm(vector<vector<int> > imageInput,int scale,int ancho, int alto,string disjoinSetStrategy) {
   this->grafo = this->imageToGraph(&imageInput,ancho, alto);;
   this->scaleProportion = scale;
   this->ancho=ancho;
   this->alto=alto;
   this->disjoinSet = selectDisjoinSetStrategy(disjoinSetStrategy);
   this->adyacentesPorComponente = inicializarMapaComoDisjoinSet(ancho*alto);
   this->disjointSetStrategy = disjoinSetStrategy;
}

SegmentationAlgorithm::~SegmentationAlgorithm() {
    if (disjoinSet != NULL) delete disjoinSet;
    if (grafo != NULL) delete grafo;
    setAdyacentesPorComponente(NULL);    
}

void SegmentationAlgorithm::setAdyacentesPorComponente(std::map<int,std::set<int>*>* adyacentesPorComponente) {
    if (this->adyacentesPorComponente != NULL) {
        for (const auto& elem : *this->adyacentesPorComponente) {
            delete elem.second;
        }
        delete this->adyacentesPorComponente;
    }
    this->adyacentesPorComponente = adyacentesPorComponente;
}


// end 2 end (componentes es el campo this->disjointSet)
vector<vector<int> > SegmentationAlgorithm::imageToSegmentation() {
    DisjoinSet* componentes = this->graphSementationIntoSets();
    return toSegmentationImage(componentes,this->ancho,this->alto);
}

DisjoinSet* SegmentationAlgorithm::graphSementationIntoSets() {
    this->disjoinSet->create(this->grafo); // crear lista de conjuntos disjunto del grafo original

    set<Edge>* edges = this->grafo->getEdgeSet(); // O(1), obtener E de G=(V,E)
    vector<Edge> edgesSortedByCost = vector<Edge>(edges->begin(), edges->end()); // O(E)
    sort(edgesSortedByCost.begin(), edgesSortedByCost.end(), edgeComparatorByCost); // O(E * log(E))

    // init thresholds
    std::vector<float> threshold;
    threshold.resize(this->grafo->getVertexSize());
    for (int i = 0; i < threshold.size(); i++)
        threshold.at(i) = tau(adyacentesPorComponente->at(i)->size());

    for(auto edge : edgesSortedByCost) {
        int indiceComponenteI = this->disjoinSet->find(edge.getLeftVertex());
        int indicecomponenteJ = this->disjoinSet->find(edge.getRigthVertex());

        if( indiceComponenteI !=  indicecomponenteJ ) {
            if((edge.getEdgeCost() <= threshold.at(indiceComponenteI)) && (edge.getEdgeCost() <= threshold.at(indicecomponenteJ))){
                this->disjoinSet->join(indiceComponenteI, indicecomponenteJ);

                this->joinComponentsOnFather(indiceComponenteI, indicecomponenteJ);

                indiceComponenteI = disjoinSet->find(indiceComponenteI);
                threshold.at(indiceComponenteI) = edge.getEdgeCost() + tau(adyacentesPorComponente->at(indiceComponenteI)->size());
            }
        }
    }

    return this->disjoinSet;
}

int SegmentationAlgorithm::minInternalDifference(int indiceComponenteI, int indicecomponenteJ) {
    set<int>* componenteI = this->adyacentesPorComponente->at(indiceComponenteI);
    set<int>* componenteJ = this->adyacentesPorComponente->at(indicecomponenteJ);
    int difCompI = internalDifference(componenteI) + tau(componenteI->size()) ;// O(KRUSKAL + grafo inducido)
    int difCompJ = internalDifference(componenteJ) + tau(componenteJ->size()) ;// O(KRUSKAL + grafo inducido)
    return std::min(difCompI , difCompJ);
}

int SegmentationAlgorithm::internalDifference(set<int> *componente) { // O(KRUSKAL + creacion del grafo inducido)
    Graph* subGrafoComponente = this->adjacencyListInducedSubGraph(this->grafo, componente);// G=(C,E) O(n)+O(m) // REDUJE COMPLEX
    DisjoinSet* disjoinSet = selectDisjoinSetStrategy(this->disjointSetStrategy);
    GetMST kruskal = GetMST(disjoinSet); // elijo la estrategia del disjoint set
    Graph* arbolRecubridorMinimoDeLaComponente = kruskal.getMST(subGrafoComponente);
    int maxWeight = arbolRecubridorMinimoDeLaComponente->getMaxWeight();
    delete arbolRecubridorMinimoDeLaComponente;
    delete disjoinSet;
    return maxWeight;
}

long SegmentationAlgorithm::tau(int cardinal) {
    int k = this->scaleProportion; // eso se setea a mano
    return k/cardinal;
}

/*
 * Este método hace un join de las dos componentes que le llegan por parámetro.
 * Hacer un join de los elementos de cada componente nos ahorra mucha memoria y tiempo de cálculo en el método
 * minInternalDifference podiendo hacerlo en O(1) y pagando el costo una sola vez.
 */
std::map<int,std::set<int>*>* SegmentationAlgorithm::joinComponentsOnFather( int fatherIndex, int sonIndex){
    this->adyacentesPorComponente->at(fatherIndex)->insert(this->adyacentesPorComponente->at(sonIndex)->begin(), this->adyacentesPorComponente->at(sonIndex)->end());
    return this->adyacentesPorComponente;
}

// para construir el subgrafo G'=(componente,E'), donde G=(V,E) y componente incluido en V
AdjacencyListGraph* SegmentationAlgorithm::adjacencyListInducedSubGraph( AdjacencyListGraph* graph, set<int> *componente) {
    int cantidadVertices = graph->getVertexSize(); // cantidad vertices V
    AdjacencyListGraph* subGraph = new AdjacencyListGraph(cantidadVertices);// O(n), estructura vacia subgrafo

    for(int vertexInComponent : *componente) {
        for (auto adyacentInOriginalGraph : *graph->getAdyacents(vertexInComponent)){
            if (componente->find(adyacentInOriginalGraph->getVertex()) != componente->end()) {
                subGraph->addEdge(vertexInComponent, adyacentInOriginalGraph->getVertex(), adyacentInOriginalGraph->getEdgeCost());
            }
        }
    }
    return subGraph;
}








/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++FIN CORE DEL ALGORITMO+++++++++++++++++++++++++++++++*/








std::map<int,std::set<int>*>* inicializarMapaComoDisjoinSet(int size){
    auto adyacentesPorComponente = new std::map<int,std::set<int>*>();
    for(int vertex = 0; vertex < size; vertex++){
        auto component = new std::set<int>();
        component->insert(vertex);
        adyacentesPorComponente->insert(std::make_pair(vertex,component));
    }
    return adyacentesPorComponente;
}

DisjoinSet *selectDisjoinSetStrategy(string strategy) {
    if(strategy == "array"){
        return new ArrayDisjoinSet();
    }else if(strategy == "tree"){
        return new TreeDisjoinSet();
    }else if( strategy == "treeCompressed"){
        return new TreeCompressedDisjoinSet();
    }else{
        return new ArrayCompressedDisjoinSet();
    }
}

// input
AdjacencyListGraph* SegmentationAlgorithm::imageToGraph(vector<vector<int> >* imagen,int ancho, int alto) {
    AdjacencyListGraph* imageGraph =  new AdjacencyListGraph(ancho*alto);
    // VERTICES= i * ancho + j (posiciones de la matriz de pixeles)
    for(int i = 0; i < alto; i = i + 1) {
        for(int j = 0; j < ancho; j = j + 1) {

            int valorActual = (*imagen)[i][j];
            int indiceVerticeActual =  i * ancho + j;

            if(i+1<alto) {
                int valorAbajo = (*imagen)[i+1][j];
                int peso = abs(valorActual-valorAbajo);
                int indiceVerticeAbajo = (i+1) * ancho + j; // mismo calculo que vertice actual
                imageGraph->addEdge(indiceVerticeActual,indiceVerticeAbajo,peso);
            }
            /*
            if (i-1>=0) {
                int valorArriba = (*imagen)[i-1][j];
                int peso = abs(valorActual-valorArriba);
                int indiceVerticeArriba = (i-1) * ancho + j;
                imageGraph->addEdge(indiceVerticeActual,indiceVerticeArriba,peso);
            }*/

            if(j+1<ancho) {
                int valorDerecha = (*imagen)[i][j+1];
                int peso = abs(valorActual-valorDerecha);
                int indiceVerticeDerecha = i * ancho + j+1;
                imageGraph->addEdge(indiceVerticeActual,indiceVerticeDerecha,peso);
            }
            /*
            if (j-1>=0) {
                int valorIzquierda = (*imagen)[i][j-1];
                int peso = abs(valorActual-valorIzquierda);
                int indiceVerticeIzquierda = i * ancho + j-1;
                imageGraph->addEdge(indiceVerticeActual,indiceVerticeIzquierda,peso);
            }*/
            /*
            if(i-1>=0 && j+1<ancho) {
                int valorDiagonalArribaDerecha = (*imagen)[i-1][j+1];
                int peso = abs(valorActual-valorDiagonalArribaDerecha);
                int indiceVerticeDiagonalArribaDerecha = (i-1)*ancho+(j+1);
                imageGraph->addEdge(indiceVerticeActual,indiceVerticeDiagonalArribaDerecha,peso);
            }
            */
            /*
            if(i-1>=0 && j-1>=0) {
                int valorDiagonalArribaIzquierda = (*imagen)[i-1][j-1];
                int peso = abs(valorActual-valorDiagonalArribaIzquierda);
                int indiceVerticeDiagonalArribaIzquierda = (i-1)*ancho+(j-1);
                imageGraph->addEdge(indiceVerticeActual,indiceVerticeDiagonalArribaIzquierda,peso);
            }*/

            if(i+1<alto && j+1<ancho) {
                int valorDiagonalAbajoDerecha = (*imagen)[i+1][j+1];
                int peso = abs(valorActual-valorDiagonalAbajoDerecha);
                int indiceVerticeDiagonalAbajoDerecha = (i+1)*ancho+(j+1);
                imageGraph->addEdge(indiceVerticeActual,indiceVerticeDiagonalAbajoDerecha,peso);
            }

            if(i+1<alto && j-1>=0) {
                int valorDiagonalAbajoIzquierda = (*imagen)[i+1][j-1];
                int peso = abs(valorActual-valorDiagonalAbajoIzquierda);
                int indiceVerticeDiagonalAbajoIzquierda = (i+1)*ancho+(j-1);
                imageGraph->addEdge(indiceVerticeActual,indiceVerticeDiagonalAbajoIzquierda,peso);
            }
        }
    }
    return imageGraph;
}

// output (componentes es el campo this->disjointSet)
vector<vector<int> >  SegmentationAlgorithm::toSegmentationImage(DisjoinSet* componentes,int ancho, int alto) {
    vector<vector<int> > matrixOutput(alto, vector<int>(ancho,0) ); // inicializo todos en cero
    for(int i = 0; i < alto; i = i + 1) {
        for(int j = 0; j < ancho; j = j + 1) {
            int indiceVertice = i * ancho + j;
            matrixOutput[i][j] = componentes->find(indiceVertice);
        }
    }
    return matrixOutput;
}

// funcion solo para testeo
int SegmentationAlgorithm::cantidadDeComponentes(vector<vector<int> > imageInput,int ancho, int alto) {
    std::list<int> indicesDeLasAreasEnLaSegmentacion;
    for(int i = 0; i < alto; i = i + 1) {
        for(int j = 0; j < ancho; j = j + 1) {
            int indiceComponente = imageInput[i][j];
            bool indiceEstaMarcada = (std::find(indicesDeLasAreasEnLaSegmentacion.begin(), indicesDeLasAreasEnLaSegmentacion.end(), indiceComponente) != indicesDeLasAreasEnLaSegmentacion.end());
            if(!indiceEstaMarcada) {
                indicesDeLasAreasEnLaSegmentacion.push_back(indiceComponente);
            }
        }
    }
    return indicesDeLasAreasEnLaSegmentacion.size();
}

// funcion solo para testeo
list<int> SegmentationAlgorithm::componentesDeLaSegmentacion(vector<vector<int> > imageInput,int ancho, int alto) {
    std::list<int> indicesDeLasAreasEnLaSegmentacion;
    for(int i = 0; i < alto; i = i + 1) {
        for(int j = 0; j < ancho; j = j + 1) {
            int indiceComponente = imageInput[i][j];
            bool indiceEstaMarcada = (std::find(indicesDeLasAreasEnLaSegmentacion.begin(), indicesDeLasAreasEnLaSegmentacion.end(), indiceComponente) != indicesDeLasAreasEnLaSegmentacion.end());
            if(!indiceEstaMarcada) {
                indicesDeLasAreasEnLaSegmentacion.push_back(indiceComponente);
            }
        }
    }
    return indicesDeLasAreasEnLaSegmentacion;
}

void SegmentationAlgorithm::setGrafo(AdjacencyListGraph* graph) {
    if (grafo != NULL) delete grafo;
    this->grafo = graph;
}

void SegmentationAlgorithm::setScaleProportion(int scaleP) {
    this->scaleProportion = scaleP;

}

void SegmentationAlgorithm::setAlto(int al)  {
    this->alto = al;

}

void SegmentationAlgorithm::setAncho(int an)  {
    this->ancho = an;

}

void SegmentationAlgorithm::setDisjointSet(DisjoinSet* disjoinSetInstance) {
    if (disjoinSet != NULL) delete disjoinSet;
    this->disjoinSet = disjoinSetInstance;
}

// en realidad es una funcion estatica
void SegmentationAlgorithm::generarFileOutput(vector<vector<int> > imageInput,int ancho, int alto, string fileNameOutput) {
    std::ofstream fileImagenSegmentada;
    fileImagenSegmentada.open(fileNameOutput,std::ios::out);
    fileImagenSegmentada << "[" ;
    for(int i = 0; i < alto; i = i + 1) {
        //fileImagenSegmentada << "(" ;
        for(int j = 0; j < ancho; j = j + 1) {
            int indiceComponente = imageInput[i][j];
            fileImagenSegmentada << indiceComponente;
            //if(j+1<ancho) {
                fileImagenSegmentada << "," ;
            //}
        }
        //fileImagenSegmentada << ")" ;
        if(i+1<alto) {
            //fileImagenSegmentada << "," ;
        }
        //fileImagenSegmentada << endl; // no
    }
    fileImagenSegmentada << "]" ;
    fileImagenSegmentada.close();
}
