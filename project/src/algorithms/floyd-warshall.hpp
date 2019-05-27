#include <iostream>
#include <vector>
#include "../entity/GasGraph.h"
#include "../utils/types.h"

using namespace std;

void floydWarshall(const GasGraph& graph, vector<vector<ulong>>& cityMinCost){
  vector<vector<ulong>> minCost(graph.getVertices());
  for (uint vertex_i = 0; vertex_i < graph.getVertices(); ++vertex_i) {
    minCost[vertex_i].assign(graph.getVertices(), infinity);
    minCost[vertex_i][vertex_i] = 0;
    for (const auto& edge_ij : graph.getNeighbors(vertex_i)) {
      uint vertex_j = edge_ij.destination;
      minCost[vertex_i][vertex_j] = edge_ij.cost;
    }
  }

  cityMinCost.resize(graph.getCities());
  for (uint city = 0; city < graph.getCities(); ++city) {
    cityMinCost[city].assign(graph.getCities(), infinity);
    cityMinCost[city][city] = 0;
  }
  
  //Algoritmo de Floyd-Warshall
  for (uint k = 0; k < graph.getVertices(); ++k) {
    for (uint i = 0; i < graph.getVertices(); ++i) {
      for (uint j = 0; j < graph.getVertices(); ++j) {
        if (minCost[i][j] >= minCost[i][k] + minCost[k][j]) {
          minCost[i][j] = minCost[i][k] + minCost[k][j];
          uint origin = graph.getCity(i),
               destination = graph.getCity(j);
          if (i == origin and minCost[i][j] < cityMinCost[origin][destination]) {
            cityMinCost[origin][destination] = minCost[i][j];
          }
        }
      }
    }
  }
}
