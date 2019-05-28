#ifndef EDGE_WEIGHTED_GRAPH_BELLMAN_FORD_HPP
#define EDGE_WEIGHTED_GRAPH_BELLMAN_FORD_HPP

#include <iostream>
#include <vector>
#include <utility>
#include "../utils/types.h"

using namespace std;

namespace bellmanFordAux {

  #define weight(edge) edge.second
  #define vertex(edge) edge.first

  void bellmanFord(uint numberOfVertices, uint sourceVertex, vector<ulong>& min,
      const vector<vector<pair<uint, ulong>>>& adjacencyList) {
    vector<bool> changed(numberOfVertices, false);
    min.assign(numberOfVertices, infinity);

    min[sourceVertex] = 0;
    changed[sourceVertex] = true;
    bool any_change = true;
    const int lastVertex = ((int) numberOfVertices) - 1;

    for(size_t i = 0; i < numberOfVertices and any_change; ++i) {
      any_change = false;
      for(int vertex = 0; vertex <= lastVertex; ++vertex) {
        if(not changed[vertex]) continue;
        changed[vertex] = false;
        for(const pair<uint, ulong>& edge : adjacencyList[vertex]) {
          if(min[vertex] + weight(edge) < min[vertex(edge)]) {
            changed[vertex(edge)] = any_change = true;
            min[vertex(edge)] = min[vertex] + weight(edge);
          }
        }
      }
    }
  }
}

#endif
