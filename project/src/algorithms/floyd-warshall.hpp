#include <iostream>
#include <vector>
#include "../entity/GasGraph.h"
#include "../utils/types.h"

using namespace std;

void floydWarshall(const GasGraph& graph, vector< vector<ulong> >& D, vector< vector<ulong> >& R){
  //transformacion de aristas a adyacencias
  //vector< vector<ulong> > D(graph.getVertices(), vector<ulong>(graph.getVertices(), infinity));  //Matriz de pesos
  D.assign(graph.getVertices(), vector<ulong>(graph.getVertices(), infinity));
  R.assign(graph.getCities(), vector<ulong>(graph.getCities(), infinity)); //El -1 es para no contar el (v, v)

  for(uint vertex = 0; vertex < graph.getVertices(); ++vertex){
    for (const auto& edge : graph.getNeighbors(vertex)) {
      //if (edge.destination < vertex) continue;
      D[vertex][edge.destination] = edge.cost;
    }
  }

  for(uint v = 0; v < graph.getVertices(); ++v){
    D[v][v] = 0;
  }

  for(uint city = 0; city < graph.getCities(); ++city){
    R[city][city] = 0;
  }
  
  //Algoritmo de Floyd-Warshall
  for(uint k = 0; k < graph.getVertices(); ++k){
      for(uint i = 0; i < graph.getVertices(); ++i) {
          for(uint j = 0; j < graph.getVertices(); ++j){
              if(D[i][j] >= D[i][k] + D[k][j]) {
                  D[i][j] = D[i][k] + D[k][j];
                  uint origin = i % graph.getCities();
                  uint destination = j % graph.getCities();
                  if(i == origin and D[i][j] < R[origin][destination] and origin != destination){
                      R[origin][destination] = D[i][j];
                  }
              }
          }
      }
  }
}
