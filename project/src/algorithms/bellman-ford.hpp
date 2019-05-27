#ifndef GAS_GRAPH_BELLMAN_FORD_HPP
#define GAS_GRAPH_BELLMAN_FORD_HPP

#include <iostream>
#include <vector>
#include "../entity/GasGraph.h"
#include "../utils/types.h"

using namespace std;

namespace bellmanFord {
  void bellmanFord(const GasGraph& graph, uint sourceVertex, vector<ulong>& realMin) {
    vector<bool> changed(graph.getVertices(), false);
    changed[sourceVertex] = true;

    vector<ulong> min(graph.getVertices(), infinity);
    vector<ulong> minVertex(graph.getVertices(), infinity);
    for (uint i = sourceVertex; i < graph.getVertices(); i+=graph.getCities()) min[i] = 0;

    realMin.assign(graph.getCities(), infinity);
    realMin[sourceVertex] = 0;

    bool anyChange = true;
    const uint lastVertex = graph.getVertices() - 1;

    for(uint i = 0; i < graph.getVertices() and anyChange; ++i) {
      anyChange = false;
      for(uint vertex = 0; vertex <= lastVertex; ++vertex) {
        if(not changed[vertex]) continue;
        changed[vertex] = false;
        for(const GasGraph::Edge& trip : graph.getNeighbors(vertex)) {

          if(min[vertex] + trip.cost < min[trip.destination]) {
            changed[trip.destination] = anyChange = true;
            min[trip.destination] = min[vertex] + trip.cost;
            min[trip.destination] = min[vertex] + trip.cost;

            uint city = graph.getCity(trip.destination);
            if (min[trip.destination] < realMin[city]) realMin[city] = min[trip.destination];
          }
        }
      }
    }

    /*cout << "origen\tdestino\tcarga final\tcosto\n";
    for (uint i = 0; i < graph.getVertices(); ++i) {
      cout << sourceVertex << "\t" << graph.getCity(i) << "\t" << i/graph.getCities() << "\t\t" << min[i] << "\n";
    }*/
  }
}


#endif
