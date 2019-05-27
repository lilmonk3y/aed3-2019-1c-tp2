#include "../GasGraph.h"
#include "../EdgeWeightedGraph.h"
#include "../../algorithms/edge-weighted-graph-bellman-ford.hpp"
#include <utility>

void GasGraph::addEdges(uint city1, uint city2, ulong gasRequired, ulong gasPrice1, ulong gasPrice2) {
  // There is one vertex for each initial charge of gas in the origin city and one vertex for each
  // final gas charge in the destination city. These two vertices are connected with an edge only if
  // the combination of initial and final gas is possible - taking into consideration the gas
  // required to travel.
  for (ulong initialGas = 0; initialGas <= tankCapacity; ++initialGas) {
    uint offsetOrigin = initialGas * cities;
    ulong minimumRefill = gasRequired > initialGas ? gasRequired - initialGas : 0;
    for (ulong refill = minimumRefill; refill <= tankCapacity - initialGas; ++refill) {
      ulong gasAfterTrip = initialGas + refill - gasRequired;
      uint offsetDest = gasAfterTrip * cities;

      adjacencyList[city1 + offsetOrigin].push_back(Trip(city2 + offsetDest, refill * gasPrice1));
      adjacencyList[city2 + offsetOrigin].push_back(Trip(city1 + offsetDest, refill * gasPrice2));
    }
  }
}

GasGraph::GasGraph(istream& istream, ulong tankCapacity) : tankCapacity(tankCapacity) {
  uint routes; // number of routes
  istream >> cities >> routes;

  // Read weight of vertices:

  vector<ulong> price(cities); // gas liter price on city
  for (uint city = 0; city < cities; ++city) istream >> price[city];

  // Read edges:

  EdgeWeightedGraph graph(cities, routes, istream);

  // Calculate minimum distance between all vertices:

  vector<vector<ulong>> min(cities);
  for (uint city = 0; city < cities; ++city) {
    bellmanFordAux::bellmanFord(cities, city, min[city], graph.getAdjacencyList());
  }

  // Finally construct this graph:

  adjacencyList.resize(getVertices());

  for (uint city1 = 0; city1 < cities; ++city1) {
    for (uint city2 = 0; city2 < cities; ++city2) {
      auto const * const edge = graph.getEdge(city1, city2);
      ulong gasRequired = edge != NULL ? edge->second : min[city1][city2];
      if (gasRequired > tankCapacity) continue;
      addEdges(city1, city2, gasRequired, price[city1], price[city2]);
    }
  }
}

uint GasGraph::getVertices() const {
  return cities * (tankCapacity + 1);
}

// Prerequisite: vertex < getVertices()
const vector<Trip>& GasGraph::getNeighbors(uint vertex) const {
  return adjacencyList[vertex];
}

uint GasGraph::getCities() const {
  return cities;
}

// Prerequisite: vertex < getVertices()
uint GasGraph::getCity(uint vertex) const {
  return vertex % getCities();
}

uint GasGraph::getTankCapacity() const {
  return tankCapacity;
}

// Prerequisite: city < getCities() and gasCharge <= getTankCapacity()
uint GasGraph::getVertex(uint city, uint gasCharge) const {
  return city + gasCharge*(getTankCapacity()+1);
}
