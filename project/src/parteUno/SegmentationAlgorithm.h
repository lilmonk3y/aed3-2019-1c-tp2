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
    //vector<vector<int> >& segmentate(Graph& graph); // grafo es la imagen hecha grafo con adyacencias
    //Graph& imageToGraph(vector<vector<int> >& imagen);
    DisjoinSet& graphSementationIntoSets(Graph& graph); // referencia

private:
    //DisjoinSet& graphSementationIntoSets(Graph& graph); // referencia
    static int minInternalDifference(DisjoinSet* disjoinSet,Graph* grafo,int componenteI, int componenteJ);
    static int internalDifference(DisjoinSet* disjoinSet,int indiceDeComponente,Graph* grafo);
    static set<int> construirComponente(DisjoinSet* disjoinSet, int componenteIndice, Graph* Imagegraph);
    static int pesoMaximo(Graph* graph);
    static int min(int a ,int b);
    static int cardinal(DisjoinSet* disjoinSet, Graph* Imagegraph, int component);
    static int tau(DisjoinSet* disjoinSet, Graph* Imagegraph, int component);
};


#endif //AED3_2019_1C_TP2_SEGMENTATIONALGORITHM_H
