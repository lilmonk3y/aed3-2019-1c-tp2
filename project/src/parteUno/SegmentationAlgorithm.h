//
// Created by Axel Arrondo on 2019-05-23.
//

#ifndef AED3_2019_1C_TP2_SEGMENTATIONALGORITHM_H
#define AED3_2019_1C_TP2_SEGMENTATIONALGORITHM_H

#include "../entity/core/Graph.h"
#include "../utils/DisjoinSet.h"
#include "../entity/core/AdjacencyListGraph.h"
#include "../utils/ArrayDisjoinSet.h"
#include "../utils/GetMST.h"
#include <set>
#include <map>
using namespace std;

class SegmentationAlgorithm {
public:
    // constructor (configuraciones):
    SegmentationAlgorithm(vector<vector<int> > imageInput,int scale,int ancho, int alto);

    // algoritmo end to end:
    vector<vector<int> > imageToSegmentation();

//protected: // comentar para los test
    // algoritmo core:
    DisjoinSet* graphSementationIntoSets(); // referencia

    // imagen a grafo, DisjoinSet a imagen (input y output):
    AdjacencyListGraph* imageToGraph(vector<vector<int> >* imagen,int ancho, int alto);
    vector<vector<int> > toSegmentationImage(DisjoinSet* componentes,int ancho, int alto);

    // solo para TESTEAR, contar la cantidad de componentes en la segmentacion:
    int cantidadDeComponentes(vector<vector<int> > imageInput,int ancho, int alto);
    void setGrafo(AdjacencyListGraph* graph);
    void setScaleProportion(int scaleP);
    void setAlto(int al);
    void setAncho(int an);

//private: // comentar para los test
    // atributos:
    AdjacencyListGraph* grafo;
    int scaleProportion;
    int ancho;
    int alto;

    // metodos del algoritmo del paper:
    int minInternalDifference(DisjoinSet* disjoinSet,int componenteI, int componenteJ);
    int internalDifference(set<int> componente);
    int tau(int cardinal);

    // metodos que deberian pertenecer a otras clases:
    set<int> construirComponente(DisjoinSet* disjoinSet, int componenteIndice);
    int min(int a ,int b);
};

#endif //AED3_2019_1C_TP2_SEGMENTATIONALGORITHM_H
