#include "../GasGraph.h"
#include "../EdgeWeightedGraph.h"
#include "../../algorithms/edge-weighted-graph-bellman-ford.hpp"
#include <utility>

void GasGraph::addEdges(uint city1, uint city2, ulong gasRequired,
    ulong gasPrice1, ulong gasPrice2) {
  for (ulong initialGas = 0; initialGas <= TANK_CAPACITY; ++initialGas) {
    uint vertex1 = city1 + initialGas * cities;
    ulong minimumRefill = gasRequired > initialGas ? gasRequired - initialGas : 0;
    for (ulong refill = minimumRefill; refill <= TANK_CAPACITY - initialGas; ++refill) {
      ulong refillCost = refill * gasPrice1;
      ulong gasAfterTrip = initialGas + refill - gasRequired;
      uint vertex2 = city2 + gasAfterTrip * cities;

      adjacencyList[vertex1].push_back(Trip(vertex2, refillCost));
    }
  }
}

GasGraph::GasGraph(istream& istream) {
  size_t routes; // number of routes
  istream >> cities >> routes;

  // Read weight of vertices:

  vector<ulong> price(cities); // gas liter price on city
  for (uint city = 0; city < cities; ++city) istream >> price[city];

  // Read edges:

  EdgeWeightedGraph graph(cities, routes, istream);

  // Calculate minimum distance between all vertices:

  vector<vector<uint>> min(cities);
  for (uint city = 0; city < cities; ++city) {
    bellmanFordAux::bellmanFord(cities, city, min[city], graph.getAdjacencyList());
  }

  // Finally construct this graph:

  adjacencyList.resize(cities*(TANK_CAPACITY+1));

  for (uint city1 = 0; city1 < cities; ++city1) {
    for (uint city2 = 0; city2 < cities; ++city2) {
      auto const * const edge = graph.getEdge(city1, city2);
      ulong gasRequired = edge != NULL ? edge->second : min[city1][city2];
      addEdges(city1, city2, gasRequired, price[city1], price[city2]);
      addEdges(city2, city1, gasRequired, price[city2], price[city1]);
    }
  }
}

size_t GasGraph::getVertices() const {
  return adjacencyList.size();
}

// Prerequisite: v < getNumberOfVertices()
const vector<Trip>& GasGraph::getNeighbors(uint vertex) const {
  return adjacencyList[vertex];
}

size_t GasGraph::getCities() const {
  return cities;
}