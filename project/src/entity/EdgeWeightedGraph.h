/*
 * Grafo con pesos en los vértices y en las aristas.
 */

#ifndef EDGE_WEIGHTED_GRAPH_H
#define EDGE_WEIGHTED_GRAPH_H

#include <vector>
#include <utility>
#include <istream>

using namespace std;

class EdgeWeightedGraph {
public:
  EdgeWeightedGraph(size_t vertices, size_t edges, istream& istream);
  pair<uint, unsigned long> const * const getEdge(uint vertex1, uint vertex2) const;
  const vector<vector<pair<uint, unsigned long>>>& getAdjacencyList() const;

private:
  vector<vector<pair<uint, unsigned long>>> adjacencyList;
};

#endif


