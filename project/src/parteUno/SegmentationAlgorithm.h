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
    SegmentationAlgorithm(AdjacencyListGraph* graph,int scale); // introducir imagen y genera adyacencias
    // algoritmo core:
    DisjoinSet* graphSementationIntoSets(); // referencia
    // imagen a grafo, DisjoinSet a imagen (input y output):
    AdjacencyListGraph* imageToGraph(vector<vector<int> >* imagen,int ancho, int alto);
    vector<vector<int> > toSegmentationImage(DisjoinSet* componentes,int ancho, int alto);

    // algoritmo end to end:
    vector<vector<int> > imageToSegmentation(vector<vector<int> > imageInput,int ancho, int alto);

    // contar la cantidad de componentes en la segmentacion:
    int cantidadDeComponentes(vector<vector<int> > imageInput,int ancho, int alto);

private:
    // atributos:
    AdjacencyListGraph* grafo;
    int scaleProportion;
    // metodos del algoritmo del paper:
    int minInternalDifference(DisjoinSet* disjoinSet,int componenteI, int componenteJ);
    int internalDifference(DisjoinSet* disjoinSet,int indiceDeComponente);
    int tau(DisjoinSet* disjoinSet,int component);
    // metodos que deberian pertenecer a otras clases:
    set<int> construirComponente(DisjoinSet* disjoinSet, int componenteIndice);
    int pesoMaximo(Graph* graph);
    int min(int a ,int b);
    int cardinal(DisjoinSet* disjoinSet, int component);
};

#endif //AED3_2019_1C_TP2_SEGMENTATIONALGORITHM_H
