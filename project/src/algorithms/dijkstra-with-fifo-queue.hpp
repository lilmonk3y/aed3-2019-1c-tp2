#ifndef GAS_GRAPH_DIJKSTRA_FIFO_HPP
#define GAS_GRAPH_DIJKSTRA_FIFO_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include "../entity/GasGraph.h"
#include "../utils/types.h"

using namespace std;

void dijkstraFifoQueue(const GasGraph& graph, uint originCity, vector<ulong>& cityMinCost,
    ulong initialGasCharge, ulong finalGasCharge) {
  vector<ulong> minCost(graph.getVertices(), infinity);
  for (ulong charge = 0; charge <= graph.getTankCapacity(); ++charge)
    minCost[graph.getVertex(originCity, charge)] = 0;
  
  cityMinCost.assign(graph.getCities(), infinity);
  cityMinCost[originCity] = 0;

  queue<tuple<ulong, uint>> costs; // <cost, dest>. Some cost of going from originCity to dest
  costs.push(make_tuple(0, graph.getVertex(originCity, initialGasCharge)));
  uint vertex_i;
  ulong cost_i;
  while (not costs.empty()) {
    tie(cost_i, vertex_i) = costs.front();
    costs.pop();

    if (cost_i > minCost[vertex_i]) continue;

    for (const auto& edge_ij : graph.getNeighbors(vertex_i)) {
      uint vertex_j = edge_ij.destination;
      ulong cost_j = minCost[vertex_i] + edge_ij.cost;

      if (cost_j < minCost[vertex_j]) {
        minCost[vertex_j] = cost_j;
        costs.push(make_tuple(cost_j, vertex_j));

        if (graph.getGasCharge(vertex_j) == finalGasCharge)
          cityMinCost[graph.getCity(vertex_j)] = cost_j;
      }
    }
  }
}

void fullDijkstraFifoQueue(const GasGraph& graph, vector<vector<ulong>>& cityMinCost,
    ulong initialGasCharge, ulong finalGasCharge) {
  for(uint originCity = 0; originCity < graph.getCities(); ++originCity) {
    dijkstraFifoQueue(graph, originCity, cityMinCost[originCity], initialGasCharge, finalGasCharge);
  }
}


#endif
