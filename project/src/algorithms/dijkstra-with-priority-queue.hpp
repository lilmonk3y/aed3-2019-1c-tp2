#ifndef GAS_GRAPH_DIJKSTRA_PRIORITY_HPP
#define GAS_GRAPH_DIJKSTRA_PRIORITY_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include "../entity/GasGraph.h"
#include "../utils/types.h"

using namespace std;

void dijkstraPriorityQueue(const GasGraph& graph, uint originCity, vector<ulong>& realMin) {
  vector<ulong> minCost(graph.getVertices(), infinity);
  for (uint i = originCity; i < graph.getVertices(); i += graph.getCities()) minCost[i] = 0;
  
  realMin.assign(graph.getCities(), infinity);
  realMin[originCity] = 0;

  priority_queue<tuple<ulong, uint>> costs; // <cost, dest>. Some cost of going from originCity to dest
  costs.push(make_tuple(0, originCity));
  uint i; // vertex i
  ulong cost_i;
  while (not costs.empty()) {
    tie(cost_i, i) = costs.top();
    costs.pop();
    
    if (cost_i > minCost[i]) continue;

    for (const auto& edge_ij : graph.getNeighbors(i)) {
      uint j = edge_ij.destination;
      ulong cost_j = minCost[i] + edge_ij.cost;

      if (cost_j < minCost[j]) {
        minCost[j] = cost_j;
        costs.push(make_tuple(cost_j, j));

        uint city = graph.getCity(j);
        if (cost_j < realMin[city]) realMin[city] = cost_j;
      }
    }
  }
}


#endif
