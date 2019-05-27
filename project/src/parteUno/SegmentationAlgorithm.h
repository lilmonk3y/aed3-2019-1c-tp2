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
    SegmentationAlgorithm(AdjacencyListGraph* graph); // introducir imagen y genera adyacencias
    DisjoinSet* graphSementationIntoSets(); // referencia

private:
    AdjacencyListGraph* grafo;
    //DisjoinSet& graphSementationIntoSets(Graph& graph); // referencia
    int minInternalDifference(DisjoinSet* disjoinSet,int componenteI, int componenteJ);
    int internalDifference(DisjoinSet* disjoinSet,int indiceDeComponente);
    set<int> construirComponente(DisjoinSet* disjoinSet, int componenteIndice);
    int pesoMaximo(Graph* graph);
    int min(int a ,int b);
    int cardinal(DisjoinSet* disjoinSet, int component);
    int tau(DisjoinSet* disjoinSet,int component);
    //vector<vector<int> >& segmentate(Graph& graph); // grafo es la imagen hecha grafo con adyacencias
    //Graph& imageToGraph(vector<vector<int> >& imagen);
};


#endif //AED3_2019_1C_TP2_SEGMENTATIONALGORITHM_H
