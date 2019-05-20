#include "../EdgeWeightedGraph.h"

EdgeWeightedGraph::EdgeWeightedGraph(size_t vertices, size_t edges, istream& istream)
    : adjacencyList(vertices) {
  for (uint i = 0; i < edges; ++i) {
    uint vertex1, vertex2;
    unsigned long weight;
    istream >> vertex1 >> vertex2 >> weight;
    adjacencyList[vertex1].push_back({vertex2, weight});
    adjacencyList[vertex2].push_back({vertex1, weight});
  }
};

// Prerequisite: v < getNumberOfVertices() and u < getNumberOfVertices()
pair<uint, unsigned long> const * const EdgeWeightedGraph::getEdge(uint vertex1, uint vertex2) const {
  for (const pair<uint, unsigned long>& edge : adjacencyList[vertex1]) {
    if (edge.first == vertex2) return &edge;
  }
  return NULL;
}

// Prerequisite: v < getNumberOfVertices()
const vector<vector<pair<uint, unsigned long>>>& EdgeWeightedGraph::getAdjacencyList() const {
  return adjacencyList;
}