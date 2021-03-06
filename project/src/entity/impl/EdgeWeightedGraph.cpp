#include "../EdgeWeightedGraph.h"

EdgeWeightedGraph::EdgeWeightedGraph(size_t vertices, size_t edges, istream& istream)
    : adjacencyList(vertices) {
  for (uint i = 0; i < edges; ++i) {
    uint vertex1, vertex2;
    ulong weight;
    istream >> vertex1 >> vertex2 >> weight;
    adjacencyList[vertex1].push_back({vertex2, weight});
    adjacencyList[vertex2].push_back({vertex1, weight});
  }
};

// Prerequisite: vertex1, vertex2 < getAdjacencyList().size()
pair<uint, ulong> const * const EdgeWeightedGraph::getEdge(uint vertex1, uint vertex2) const {
  for (const pair<uint, ulong>& edge : adjacencyList[vertex1]) {
    if (edge.first == vertex2) return &edge;
  }
  return NULL;
}

const vector<vector<pair<uint, ulong>>>& EdgeWeightedGraph::getAdjacencyList() const {
  return adjacencyList;
}