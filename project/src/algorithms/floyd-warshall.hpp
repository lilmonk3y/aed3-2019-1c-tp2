#include <iostream>
#include <vector>
#include "../entity/GasGraph.h"
#include "../misc/defines.h"

using namespace std;

void floydWarshall(const GasGraph& graph, vector<vector<ulong>>& cityMinCost,
    ulong initialGasCharge, ulong finalGasCharge) {
  vector<vector<ulong>> minCost(graph.getVertices());
  for (uint vertex_i = 0; vertex_i < graph.getVertices(); ++vertex_i) {
    minCost[vertex_i].assign(graph.getVertices(), infinity);
    for (const auto& edge_ij : graph.getNeighbors(vertex_i)) {
      uint vertex_j = edge_ij.destination;
      minCost[vertex_i][vertex_j] = edge_ij.cost;
    }
    for (ulong charge = 0; charge <= graph.getTankCapacity(); ++charge)
      minCost[vertex_i][graph.getVertex(vertex_i, charge)] = 0;
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

          if (graph.getGasCharge(i) == initialGasCharge and
              graph.getGasCharge(j) == finalGasCharge)
            cityMinCost[graph.getCity(i)][graph.getCity(j)] = minCost[i][j];
        }
      }
    }
  }
}
