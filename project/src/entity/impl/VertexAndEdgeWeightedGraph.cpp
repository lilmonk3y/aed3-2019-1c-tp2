#include "../VertexAndEdgeWeightedGraph.h"

VertexAndEdgeWeightedGraph::VertexAndEdgeWeightedGraph(size_t numberOfVertices)
  : adjacencyList(numberOfVertices), vertexWeight(numberOfVertices) {};

size_t VertexAndEdgeWeightedGraph::getNumberOfVertices() const {
  return adjacencyList.size();
}

// Prerequisite: v < getNumberOfVertices()
void VertexAndEdgeWeightedGraph::setVertexWeight(Vertex v, Weight w) {
  vertexWeight[v] = w;
}

// Prerequisite: v < getNumberOfVertices()
Weight VertexAndEdgeWeightedGraph::getVertexWeight(Vertex v) const {
  return vertexWeight[v];
}

/*// Prerequisite: v < getNumberOfVertices() and u < getNumberOfVertices()
bool VertexAndEdgeWeightedGraph::adjacent(Vertex v, Vertex u) const {
  for (const DestinationEdge& edge : getNeighbors(v)) {
    if (edge.vertex == u) return true;
  }
  return false;
}*/

// Prerequisite: v < getNumberOfVertices() and u < getNumberOfVertices() and not adjacent(v, w)
void VertexAndEdgeWeightedGraph::addEdge(Vertex v, Vertex u, Weight w) {
  adjacencyList[v].push_back(DestinationEdge(u, w));
  adjacencyList[u].push_back(DestinationEdge(v, w));
}

// Prerequisite: v < getNumberOfVertices()
const std::vector<DestinationEdge>& VertexAndEdgeWeightedGraph::getNeighbors(Vertex v) const {
  return adjacencyList[v];
}