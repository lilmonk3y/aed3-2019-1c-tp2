//
// Created by Axel Arrondo on 2019-05-23.
//

#include "SegmentationAlgorithm.h"
#include <set>
#include <iostream>

SegmentationAlgorithm::SegmentationAlgorithm(AdjacencyListGraph* graph, int scale) {
   this->grafo = graph;
   this->scaleProportion = scale;
}


DisjoinSet* SegmentationAlgorithm::graphSementationIntoSets() {
    DisjoinSet* disjoinSet = new ArrayDisjoinSet();
    disjoinSet->create(grafo); // crear lista de conjuntos disjunto del grafo original

    vector<Edge>* edges = grafo->getEdges(); // obtener E de G=(V,E)
    // lo siguiente ordena los ejes de manera creciente respecto de sus pesos:
    sort(edges->begin(),edges->end()); // ordenar con quick sort, de manera no-decreciente la lista de todos los ejes

    for(vector <Edge> :: iterator edge = edges->begin(); edge != edges->end(); ++edge) {// itero todos los ejes.
        int indiceComponenteI = disjoinSet->find(edge->getLeftVertex()); // busco componente vertice i, extremo del eje
        int indicecomponenteJ = disjoinSet->find(edge->getRigthVertex());// busco componente vertice j, extremo del eje

        if( indiceComponenteI !=  indicecomponenteJ ) {
            if( edge->getEdgeCost() <= minInternalDifference(disjoinSet,indiceComponenteI,indicecomponenteJ) ) {
                disjoinSet->join(indiceComponenteI, indicecomponenteJ); // union componentes a las cuales pertenece los vertices
            }
        }
    }
    return disjoinSet;
}

int SegmentationAlgorithm::minInternalDifference(DisjoinSet* disjoinSet,int componenteI, int componenteJ) {
    int difCompI = internalDifference(disjoinSet,componenteI) + tau(disjoinSet, componenteI) ;
    int difCompJ = internalDifference(disjoinSet,componenteJ) + tau(disjoinSet, componenteJ) ;
    return min(difCompI , difCompJ);
}

// implementar max(conjuntoDeLosPesos, eso solo
int SegmentationAlgorithm::internalDifference(DisjoinSet* disjoinSet,int indiceDeComponente) {
    set<int> componente = construirComponente(disjoinSet,indiceDeComponente);

    Graph* subGrafoComponente = AdjacencyListGraph::adjacencyListInducedSubGraph(this->grafo,componente);// G=(C,E)
    GetMST kruskal = GetMST(new ArrayDisjoinSet());// elijo la estrategia del disjoint set
    Graph* arbolRecubridorMinimoDeLaComponente = kruskal.getMST(subGrafoComponente); // type AdjacencyListGraph

    return pesoMaximo(arbolRecubridorMinimoDeLaComponente);
}

// esto lo deberia hacer el disjoint set, reconstruir un conjunto disjunto
// queda desprolijo el imageGraph
// esto esta bien implementado:
set<int> SegmentationAlgorithm::construirComponente(DisjoinSet* disjoinSet, int indiceDeComponente) {
    std::set<int>  componenteVertices;
    int quantityVertex = this->grafo->getVertex(); // cantidad de vertices
    for(int indexVertex=0; indexVertex < quantityVertex; indexVertex++) {
        if  (disjoinSet->find(indexVertex) == indiceDeComponente) {
            componenteVertices.insert(indexVertex);
        }
    }
    return componenteVertices;
}

int SegmentationAlgorithm::tau(DisjoinSet* disjoinSet, int component) {
    int k = this->scaleProportion; // eso se setea a mano
    return k/cardinal(disjoinSet,component);
}

// no deberia implementarse esto aca, sino dentro del disjoint set
// Graph se usa solo para el cardinal de vertices
int SegmentationAlgorithm::cardinal(DisjoinSet* disjoinSet,int component) {
    int quantityVertex = this->grafo->getVertex();
    int cardinal = 0;
    for(int indexVertex=0; indexVertex<quantityVertex; indexVertex++) {
        if  (disjoinSet->find(indexVertex) == component) {
            cardinal = cardinal +1;
        }
    }
    return cardinal;
}

int SegmentationAlgorithm::min(int a ,int b) {
    if(a<b){
        return a;
    }
    return b;
}

int SegmentationAlgorithm::pesoMaximo(Graph* subgrafo) {
    int pesoMaximo = 0;
    vector<Edge>* ejes = subgrafo->getEdges();
    for(auto eje : *ejes) {
        if( pesoMaximo < eje.getEdgeCost() ) {
            pesoMaximo = eje.getEdgeCost();
        }
    }
    return pesoMaximo;
}

// input
AdjacencyListGraph* SegmentationAlgorithm::imageToGraph(vector<vector<int> >* imagen,int ancho, int alto) {
    AdjacencyListGraph* imageGraph =  new AdjacencyListGraph(ancho*alto);
    // VERTICES= i * ancho + j (posiciones de la matriz de pixeles)
    // ver si agregando dos veces mismo eje ya sabe que fue agregado previamente!!!!!!!!!!!!!!!
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
            cout << matrixOutput[i][j] << "    ";
        }
        cout << endl;
    }
    return matrixOutput;
}

vector<vector<int> > SegmentationAlgorithm::imageToSegmentation(vector<vector<int> > imageInput,int ancho, int alto) {
    AdjacencyListGraph* grafoDeLaImagen = imageToGraph(&imageInput,ancho,alto);
    SegmentationAlgorithm* segmentationAlgorithm = new SegmentationAlgorithm(grafoDeLaImagen,100);
    DisjoinSet* componentes = segmentationAlgorithm->graphSementationIntoSets();
    return toSegmentationImage(componentes,ancho,alto);
}

int SegmentationAlgorithm::cantidadDeComponentes(vector<vector<int> > imageInput,int ancho, int alto) {
    std::list<int> indicesDeLasAreasEnLaSegmentacion;
    for(int i = 0; i < alto; i = i + 1) {
        for(int j = 0; j < ancho; j = j + 1) {
            int indiceComponente = imageInput[i][j];
            bool indiceEstaMarcada = (std::find(indicesDeLasAreasEnLaSegmentacion.begin(), indicesDeLasAreasEnLaSegmentacion.end(), indiceComponente) != indicesDeLasAreasEnLaSegmentacion.end());
            if(!indiceEstaMarcada) {
                cout << indiceComponente << endl; // MOSTRAR LOS VALORES
                indicesDeLasAreasEnLaSegmentacion.push_back(indiceComponente);
            }
        }
    }
    return indicesDeLasAreasEnLaSegmentacion.size();
}
