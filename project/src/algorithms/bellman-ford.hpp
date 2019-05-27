#ifndef GAS_GRAPH_BELLMAN_FORD_HPP
#define GAS_GRAPH_BELLMAN_FORD_HPP

#include <iostream>
#include <vector>
#include "../entity/GasGraph.h"
#include "../utils/types.h"

using namespace std;

void bellmanFord(const GasGraph& graph, uint originCity, vector<ulong>& cityMinCost,
    ulong initialGasCharge, ulong finalGasCharge) {
  vector<bool> changed(graph.getVertices(), false);
  changed[graph.getVertex(originCity, initialGasCharge)] = true;

  vector<ulong> minCost(graph.getVertices(), infinity);
  for (ulong charge = 0; charge <= graph.getTankCapacity(); ++charge)
    minCost[graph.getVertex(originCity, charge)] = 0;

  cityMinCost.assign(graph.getCities(), infinity);
  cityMinCost[originCity] = 0;

  bool anyChange = true;

  for (uint repetition = 0; repetition < graph.getVertices() and anyChange; ++repetition) {
    anyChange = false;
    for (uint vertex_i = 0; vertex_i < graph.getVertices(); ++vertex_i) {
      if (changed[vertex_i]) {
        changed[vertex_i] = false;
        for(const GasGraph::Edge& edge_ij : graph.getNeighbors(vertex_i)) {
          uint vertex_j = edge_ij.destination;

          if (minCost[vertex_j] > minCost[vertex_i] + edge_ij.cost) {
            minCost[vertex_j] = minCost[vertex_i] + edge_ij.cost;
            changed[vertex_j] = anyChange = true;

            if (graph.getGasCharge(vertex_j) == finalGasCharge)
              cityMinCost[graph.getCity(vertex_j)] = minCost[vertex_j];
          }
        }
      }
    }
  }
}


#endif
