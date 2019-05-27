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
    DisjoinSet* graphSementationIntoSets(); // referencia
    AdjacencyListGraph* imageToGraph(vector<vector<int> >* imagen,int ancho, int alto);

private:
    AdjacencyListGraph* grafo;
    int scaleProportion;
    int minInternalDifference(DisjoinSet* disjoinSet,int componenteI, int componenteJ);
    int internalDifference(DisjoinSet* disjoinSet,int indiceDeComponente);
    set<int> construirComponente(DisjoinSet* disjoinSet, int componenteIndice);
    int pesoMaximo(Graph* graph);
    int min(int a ,int b);
    int cardinal(DisjoinSet* disjoinSet, int component);
    int tau(DisjoinSet* disjoinSet,int component);
};


#endif //AED3_2019_1C_TP2_SEGMENTATIONALGORITHM_H
