//
// Created by Axel Arrondo on 2019-05-23.
//

#include "SegmentationAlgorithm.h"
#include <set>
#include <iostream>
#include <fstream>
#include <algorithm>

SegmentationAlgorithm::SegmentationAlgorithm(vector<vector<int> > imageInput,int scale,int ancho, int alto,DisjoinSet* disjoinSetInstance) {
   this->grafo = this->imageToGraph(&imageInput,ancho, alto);
   this->scaleProportion = scale;
   this->ancho=ancho;
   this->alto=alto;
   this->disjoinSet = disjoinSetInstance;
   this->imagen = &imageInput;// quitar referencia
}

DisjoinSet* SegmentationAlgorithm::graphSementationIntoSets() {
    this->disjoinSet->create(this->grafo); // crear lista de conjuntos disjunto del grafo original

    set<Edge>* edges = this->grafo->getEdgeSet(); // O(1), obtener E de G=(V,E)

    for(auto edge : *edges) { // itero todos los ejes. (estan ordenados de manera creciente)
        int indiceComponenteI = this->disjoinSet->find(edge.getLeftVertex()); // O(1),busco componente vertice i, extremo del eje
        int indicecomponenteJ = this->disjoinSet->find(edge.getRigthVertex());// O(1),busco componente vertice j, extremo del eje

        if( indiceComponenteI !=  indicecomponenteJ ) {
            if( edge.getEdgeCost() <= minInternalDifference(indiceComponenteI,indicecomponenteJ) ) {
                this->disjoinSet->join(indiceComponenteI, indicecomponenteJ); // O(join del disjointSet),union componentes a las cuales pertenece los vertices
            }
        }
    }
    return this->disjoinSet;
}

int SegmentationAlgorithm::minInternalDifference(int indiceComponenteI, int indicecomponenteJ) {
    set<int>* componenteI = construirComponente(indiceComponenteI); // SIGMA(n),  VER SI SE PUEDE REDUCIR MAS
    set<int>* componenteJ = construirComponente(indicecomponenteJ); // SIGMA(n), VER SI SE PUEDE REDUCIR MAS
    int difCompI = internalDifference(componenteI) + tau(componenteI.size()) ;// O(KRUSKAL + grafo inducido)
    int difCompJ = internalDifference(componenteJ) + tau(componenteJ.size()) ;// O(KRUSKAL + grafo inducido)
    return min(difCompI , difCompJ); // O(1)
}

int SegmentationAlgorithm::internalDifference(set<int>* componente) { // O(KRUSKAL + creacion del grafo inducido)
    //Graph* subGrafoComponente = this->grafo->adjacencyListInducedSubGraph(componente);// G=(C,E) O(n)+O(m) // REDUJE COMPLEX
    Graph* subGrafoComponente = obtenerSubgrafo(componente,this->imagen,this->ancho,this->alto);
    GetMST kruskal = GetMST(new ArrayDisjoinSet()); // elijo la estrategia del disjoint set
    Graph* arbolRecubridorMinimoDeLaComponente = kruskal.getMST(subGrafoComponente); // REDUJE COMPLEX
    return arbolRecubridorMinimoDeLaComponente->getMaxWeight();// O(1) // REDUJE COMPLEX
}

// esto lo deberia hacer el disjoint set, reconstruir un conjunto disjunto dado un indice de una componente
set<int>* SegmentationAlgorithm::construirComponente(int indiceDeComponente) {
    std::set<int>*  componenteVertices = new set<int>();
    int quantityVertex = this->grafo->getVertex(); // O(1), cantidad de vertices del grafo
    for(int indexVertex=0; indexVertex < quantityVertex; indexVertex++) {
        if  (this->disjoinSet->find(indexVertex) == indiceDeComponente) {
            componenteVertices.insert(indexVertex);
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

// end 2 end (componentes es el campo this->disjointSet)
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



Graph* SegmentationAlgorithm::obtenerSubgrafo(set<int>* componente,vector<vector<int> >* imagen,int ancho,int alto) { // costo O(n).logn
    // vertices vecinos que pertenezcan a la componente
    // con la imagen genero ejes con pesos
    // indiceVertice = i*ancho + j
    AdjacencyListGraph* subgrafo = new AdjacencyListGraph(ancho*alto);

    //set<Edge>* ejes = new set<Edge>();

    for(auto vertice: *componente) {
        int i = vertice/ancho;//cociente
        int j = vertice%ancho;//resto
        int  valorActual = (*imagen)[i][j];


        int indiceVerticeAbajo = (i+1) * ancho + j; // mismo calculo que vertice actual
        const bool indiceVerticeAbajo_is_in  = componente->find(indiceVerticeAbajo) != componente->end();
        if(i+1<alto && indiceVerticeAbajo_is_in) {
            int valorAbajo = (*imagen)[i+1][j];
            int peso = abs(valorActual-valorAbajo);
            //imageGraph->addEdge(indiceVerticeActual,indiceVerticeAbajo,peso);
            //Edge e(vertice,indiceVerticeAbajo,peso);
            //ejes->insert(e);
            subgrafo->addEdge(vertice,indiceVerticeAbajo,peso);
        }

        int indiceVerticeArriba = (i-1) * ancho + j;
        const bool indiceVerticeArriba_is_in  = componente->find(indiceVerticeArriba) != componente->end();
        if (i-1>=0 && indiceVerticeArriba_is_in) {
            int valorArriba = (*imagen)[i-1][j];
            int peso = abs(valorActual-valorArriba);
            //imageGraph->addEdge(indiceVerticeActual,indiceVerticeArriba,peso);
            //Edge e(vertice,indiceVerticeArriba,peso);
            //ejes->insert(e);
            subgrafo->addEdge(vertice,indiceVerticeArriba,peso);
        }

        int indiceVerticeDerecha = i * ancho + j+1;
        const bool indiceVerticeDerecha_is_in  = componente->find(indiceVerticeDerecha) != componente->end();
        if(j+1<ancho && indiceVerticeDerecha_is_in) {
            int valorDerecha = (*imagen)[i][j+1];
            int peso = abs(valorActual-valorDerecha);
            //imageGraph->addEdge(indiceVerticeActual,indiceVerticeDerecha,peso);

            //Edge e( vertice,indiceVerticeDerecha,peso);
            //ejes->insert(e);
            subgrafo->addEdge(vertice,indiceVerticeDerecha,peso);
        }

        int indiceVerticeIzquierda = i * ancho + j-1;
        const bool indiceVerticeIzquierda_is_in  = componente->find(indiceVerticeIzquierda) != componente->end();
        if (j-1>=0 && indiceVerticeIzquierda_is_in) {
            int valorIzquierda = (*imagen)[i][j-1];
            int peso = abs(valorActual-valorIzquierda);
            //imageGraph->addEdge(indiceVerticeActual,indiceVerticeIzquierda,peso);

            //Edge e( vertice,indiceVerticeIzquierda,peso);
            //ejes->insert(e);
            subgrafo->addEdge( vertice,indiceVerticeIzquierda,peso);
        }

        int indiceVerticeDiagonalArribaDerecha = (i-1)*ancho+(j+1);
        const bool indiceVerticeDiagonalArribaDerecha_is_in  = componente->find(indiceVerticeIzquierda) != componente->end();
        if(i-1>=0 && j+1<ancho && indiceVerticeDiagonalArribaDerecha_is_in) {
            int valorDiagonalArribaDerecha = (*imagen)[i-1][j+1];
            int peso = abs(valorActual-valorDiagonalArribaDerecha);
            //imageGraph->addEdge(indiceVerticeActual,indiceVerticeDiagonalArribaDerecha,peso);

            //Edge e( vertice,indiceVerticeDiagonalArribaDerecha,peso);
            //ejes->insert(e);
            subgrafo->addEdge(vertice,indiceVerticeDiagonalArribaDerecha,peso);
        }

        int indiceVerticeDiagonalArribaIzquierda = (i-1)*ancho+(j-1);
        const bool indiceVerticeDiagonalArribaIzquierda_is_in  = componente->find(indiceVerticeIzquierda) != componente->end();
        if(i-1>=0 && j-1>=0 && indiceVerticeDiagonalArribaIzquierda_is_in) {
            int valorDiagonalArribaIzquierda = (*imagen)[i-1][j-1];
            int peso = abs(valorActual-valorDiagonalArribaIzquierda);
            //imageGraph->addEdge(indiceVerticeActual,indiceVerticeDiagonalArribaIzquierda,peso);

            //Edge e( vertice,indiceVerticeDiagonalArribaIzquierda,peso);
            //ejes->insert(e);
            subgrafo->addEdge(vertice,indiceVerticeDiagonalArribaIzquierda,peso);
        }

        int indiceVerticeDiagonalAbajoDerecha = (i+1)*ancho+(j+1);
        const bool indiceVerticeDiagonalAbajoDerecha_is_in  = componente->find(indiceVerticeDiagonalAbajoDerecha) != componente->end();
        if(i+1<alto && j+1<ancho && indiceVerticeDiagonalAbajoDerecha_is_in) {
            int valorDiagonalAbajoDerecha = (*imagen)[i+1][j+1];
            int peso = abs(valorActual-valorDiagonalAbajoDerecha);
            //imageGraph->addEdge(indiceVerticeActual,indiceVerticeDiagonalAbajoDerecha,peso);

            //Edge e( vertice,indiceVerticeDiagonalAbajoDerecha,peso);
            //ejes->insert(e);
            subgrafo->addEdge(vertice,indiceVerticeDiagonalAbajoDerecha,peso);
        }

        int indiceVerticeDiagonalAbajoIzquierda = (i+1)*ancho+(j-1);
        const bool indiceVerticeDiagonalAbajoIzquierda_is_in  = componente->find(indiceVerticeDiagonalAbajoDerecha) != componente->end();
        if(i+1<alto && j-1>=0 && indiceVerticeDiagonalAbajoIzquierda_is_in) {
            int valorDiagonalAbajoIzquierda = (*imagen)[i+1][j-1];
            int peso = abs(valorActual-valorDiagonalAbajoIzquierda);
            //imageGraph->addEdge(indiceVerticeActual,indiceVerticeDiagonalAbajoIzquierda,peso);

            //Edge e( vertice,indiceVerticeDiagonalAbajoIzquierda,peso);
            //ejes->insert(e);
            subgrafo->addEdge(vertice,indiceVerticeDiagonalAbajoIzquierda,peso);
        }


    }
    //return ejes;
    return subgrafo;
}