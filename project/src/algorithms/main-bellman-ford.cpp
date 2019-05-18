#include <iostream>
#include <vector>
#include <limits>
#include "../entity/VertexAndEdgeWeightedGraph.h"

using namespace std;

// Realiza el cálculo de camino mínimo tomando los pesos de las aristas. Falta considerar los pesos
// de los vértices y realizar el cálculo de nafta mínima.

const int infinity = numeric_limits<int>::max() / 2 - 1;

void bellmanFord(VertexAndEdgeWeightedGraph& graph, int sourceVertex, vector<int>& min) {
  vector<int> changed(graph.getNumberOfVertices(), false);
  min.assign(graph.getNumberOfVertices(), infinity);

  min[sourceVertex] = 0;
  changed[sourceVertex] = true;
  bool any_change = true;
  const int lastVertex = ((int) graph.getNumberOfVertices()) - 1;

  for(size_t i = 0; i < graph.getNumberOfVertices() and any_change; ++i) {
    any_change = false;
    for(int vertex = 0; vertex <= lastVertex; ++vertex) {
      if(not changed[vertex]) continue;
      changed[vertex] = false;
      for(const DestinationEdge& edge : graph.getNeighbors(vertex)) {
        if(min[vertex] + edge.weight < min[edge.vertex]) {
          changed[edge.vertex] = any_change = true;
          min[edge.vertex] = min[vertex] + edge.weight;
        }
      }
    }
  }
}

int main() {
  // Lectura de la entrada:
  DestinationEdge a = DestinationEdge(5, 6);

  int numberOfVertices, numberOfEdges;
  cin >> numberOfVertices >> numberOfEdges;

  VertexAndEdgeWeightedGraph graph(numberOfVertices);
  for (int vertex = 0; vertex < numberOfVertices; ++vertex) {
    long weight;
    cin >> weight;
    graph.setVertexWeight(vertex, weight);
  }
  for(int i = 0; i < numberOfEdges; ++i) {
    int vertex1, vertex2;
    long weight;
    cin >> vertex1 >> vertex2 >> weight;
    graph.addEdge(vertex1, vertex2, weight);
  }

  // Cálculo de caminos mínimos:

  vector<vector<int>> min(numberOfVertices); // min[i][j] = peso del camino de i a j con peso mínimo
  for(int sourceVertex = 0; sourceVertex < numberOfVertices; ++sourceVertex) {
    bellmanFord(graph, sourceVertex, min[sourceVertex]);
  }

  // Impresión de la salida:

  for (int sourceVertex = 0; sourceVertex < numberOfVertices; ++sourceVertex) {
    for (int destVertex = sourceVertex + 1; destVertex < numberOfVertices; ++destVertex) {
      cout << sourceVertex << " " << destVertex << " "
           << min[sourceVertex][destVertex] << endl;
    } 
  }
  
  return 0;
}