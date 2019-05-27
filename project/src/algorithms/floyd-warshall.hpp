#include <iostream>
#include <vector>
#include "../entity/GasGraph.h"
#include "../utils/types.h"

using namespace std;

void floydWarshall(const GasGraph& graph, vector< vector<ulong> >& D){
  //transformacion de aristas a adyacencias
  //vector< vector<ulong> > D(graph.getVertices(), vector<ulong>(graph.getVertices(), infinity));  //Matriz de pesos

  for(uint vertex = 0; vertex < graph.getVertices(); ++vertex){
    for (const auto& edge : graph.getNeighbors(vertex)) {
      if (edge.destination < vertex) continue;
      D[vertex][edge.destination] = edge.cost;
    }
  }

  for(uint v = 0; v < graph.getVertices(); ++v) {D[v][v] = 0;}
  
  //Algoritmo de Floyd-Warshall
  bool c = false;                      //Existe ciclo negativo
  for(uint k = 0; k < graph.getVertices() and not c; ++k) for(uint i = 0; i < graph.getVertices() and not c; ++i) {
    for(uint j = 0; j < graph.getVertices(); ++j) if(D[i][j] > D[i][k] + D[k][j]) {
      D[i][j] = D[i][k] + D[k][j];
    }
    c = D[i][i] < 0;
  }
}
