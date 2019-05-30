//
// Created by Axel Arrondo on 2019-05-23.
//

#include "SegmentationAlgorithm.h"
#include <set>
#include <iostream>
#include <fstream>

SegmentationAlgorithm::SegmentationAlgorithm(vector<vector<int> > imageInput,int scale,int ancho, int alto,DisjoinSet* disjoinSetInstance) {
   this->grafo = this->imageToGraph(&imageInput,ancho, alto);;
   this->scaleProportion = scale;
   this->ancho=ancho;
   this->alto=alto;
   this->disjoinSet = disjoinSetInstance;
}

DisjoinSet* SegmentationAlgorithm::graphSementationIntoSets() {
    disjoinSet->create(this->grafo); // crear lista de conjuntos disjunto del grafo original

    set<Edge>* edges = this->grafo->getEdgeSet(); // O(1), obtener E de G=(V,E)

    for(auto edge : *edges) { // itero todos los ejes. (estan ordenados de manera creciente al usar el tipo set)
        int indiceComponenteI = disjoinSet->find(edge.getLeftVertex()); // O(1),busco componente vertice i, extremo del eje
        int indicecomponenteJ = disjoinSet->find(edge.getRigthVertex());// O(1),busco componente vertice j, extremo del eje

        if( indiceComponenteI !=  indicecomponenteJ ) {
            if( edge.getEdgeCost() <= minInternalDifference(disjoinSet,indiceComponenteI,indicecomponenteJ) ) {
                disjoinSet->join(indiceComponenteI, indicecomponenteJ); // O(join del disjointSet),union componentes a las cuales pertenece los vertices
            }
        }
    }
    return disjoinSet;
}

int SegmentationAlgorithm::minInternalDifference(DisjoinSet* disjoinSet,int indiceComponenteI, int indicecomponenteJ) {
    set<int>* componenteI = disjoinSet->getSet(indiceComponenteI);//construirComponente(disjoinSet,indiceComponenteI); // VER SI SE PUEDE REDUCIR MAS
    set<int>* componenteJ = disjoinSet->getSet(indicecomponenteJ);//construirComponente(disjoinSet,indicecomponenteJ); // VER SI SE PUEDE REDUCIR MAS
    int difCompI = internalDifference(componenteI) + tau(componenteI->size()) ;// O(KRUSKAL + grafo inducido)
    int difCompJ = internalDifference(componenteJ) + tau(componenteJ->size()) ;// O(KRUSKAL + grafo inducido)
    return min(difCompI , difCompJ); // O(1)
}

int SegmentationAlgorithm::internalDifference(set<int>* componente) {// O(KRUSKAL + creacion del grafo inducido)
    Graph* subGrafoComponente = this->grafo->adjacencyListInducedSubGraph(componente);// G=(C,E) O(n)+O(m) // REDUJE COMPLEX
    GetMST kruskal = GetMST(new ArrayDisjoinSet());// elijo la estrategia del disjoint set
    Graph* arbolRecubridorMinimoDeLaComponente = kruskal.getMST(subGrafoComponente); // REDUJE COMPLEX
    return arbolRecubridorMinimoDeLaComponente->getMaxWeight();// O(1) // REDUJE COMPLEX
}

// esto lo deberia hacer el disjoint set, reconstruir un conjunto disjunto
set<int> SegmentationAlgorithm::construirComponente(DisjoinSet* disjoinSet, int indiceDeComponente) {
    std::set<int>  componenteVertices;
    int quantityVertex = this->grafo->getVertex(); // cantidad de vertices
    for(int indexVertex=0; indexVertex < quantityVertex; indexVertex++) {
        if  (disjoinSet->find(indexVertex) == indiceDeComponente) { // costo del find
            componenteVertices.insert(indexVertex);// o(1) amortizado, sino o(log n)
        }
    }
    return componenteVertices;
}

int SegmentationAlgorithm::tau(int cardinal) {
    int k = this->scaleProportion; // eso se setea a mano
    return k/cardinal;
}

int SegmentationAlgorithm::min(int a ,int b) {
    if(a<b){
        return a;
    }
    return b;
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

// output
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

// end 2 end
vector<vector<int> > SegmentationAlgorithm::imageToSegmentation() {
    DisjoinSet* componentes = this->graphSementationIntoSets();
    return toSegmentationImage(componentes,this->ancho,this->alto);
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
    this->disjoinSet = disjoinSetInstance;
}

// en realidad es una funcion estatica
void SegmentationAlgorithm::generarFileOutput(vector<vector<int> > imageInput,int ancho, int alto) {
    std::ofstream fileImagenSegmentada;
    fileImagenSegmentada.open("imagen-segmentada",std::ios::out);
    fileImagenSegmentada << "[" ;
    for(int i = 0; i < alto; i = i + 1) {
        fileImagenSegmentada << "(" ;
        for(int j = 0; j < ancho; j = j + 1) {
            int indiceComponente = imageInput[i][j];
            fileImagenSegmentada << indiceComponente;
            if(j+1<ancho) {
                fileImagenSegmentada << "," ;
            }
        }
        fileImagenSegmentada << ")" ;
        if(i+1<alto) {
            fileImagenSegmentada << "," ;
        }
        //fileImagenSegmentada << endl;
    }
    fileImagenSegmentada << "]" ;
    fileImagenSegmentada.close();
}