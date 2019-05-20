#ifndef GAS_GRAPH_BELLMAN_FORD_HPP
#define GAS_GRAPH_BELLMAN_FORD_HPP

#include <iostream>
#include <vector>
#include <limits>
#include "../entity/GasGraph.h"

using namespace std;

namespace bellmanFord {
  const ulong infinity = numeric_limits<uint>::max() / 2 - 1;

  void bellmanFord(const GasGraph& graph, uint sourceVertex, vector<ulong>& realMin) {
    vector<bool> changed(graph.getVertices(), false);
    vector<ulong> min(graph.getVertices(), infinity);
    realMin.assign(graph.getCities(), infinity);

    min[sourceVertex] = 0;
    changed[sourceVertex] = true;
    bool any_change = true;
    const uint lastVertex = graph.getVertices() - 1;

    for(uint i = 0; i < graph.getVertices() and any_change; ++i) {
      any_change = false;
      for(uint vertex = 0; vertex <= lastVertex; ++vertex) {
        if(not changed[vertex]) continue;
        changed[vertex] = false;
        for(const Trip& trip : graph.getNeighbors(vertex)) {

          if(min[vertex] + trip.cost < min[trip.destination]) {
            changed[trip.destination] = any_change = true;
            min[trip.destination] = min[vertex] + trip.cost;

            uint city = trip.destination % graph.getCities();
            if (min[trip.destination] < realMin[city]) realMin[city] = min[trip.destination];
          }
        }
      }
    }
  }
}

#endif