/*
 * Grafo con pesos en los vértices y en las aristas.
 */

#include <vector>

using Vertex = int;
using Weight = long;

typedef struct s_DestinationEdge {
    Vertex vertex;
    Weight weight;

    s_DestinationEdge(Vertex v, Weight w) : vertex(v), weight(w) {};
} DestinationEdge;

class VertexAndEdgeWeightedGraph {
public:
    VertexAndEdgeWeightedGraph(size_t numberOfVertices);
    size_t getNumberOfVertices() const;
    void setVertexWeight(Vertex v, Weight w);
    Weight getVertexWeight(Vertex v) const;
    //bool adjacent(Vertex v, Vertex u) const;
    void addEdge(Vertex v, Vertex u, Weight w);
    const std::vector<DestinationEdge>& getNeighbors(Vertex v) const;

private:
    std::vector<std::vector<DestinationEdge>> adjacencyList;
    std::vector<Weight> vertexWeight;
};


