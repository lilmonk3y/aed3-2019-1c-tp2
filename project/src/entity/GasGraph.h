/*
 * Grafo especialmente diseñado para el problema de calcular el mínimo costo de nafta entre dos
 * ciudades.
 *
 * A partir del grafo de ciudades que se recibe como parámetro se construye el siguiente grafo:
 * - Se le agregan todas las aristas necesarias para hacerlo completo.
 * - Cada arista agregada va con el peso del camino mínimo calculado en base a las distancias entre
 *   las ciudades (no en base al costo de la nafta).
 * - Las aristas originales conservan su distancia original.
 * - Esto es para permitir que se pueda pasar por una ciudad sin detenerse a cargar nafta en ella,
 *   ya que, en este modelo, si un vértice pertenece a un camino significa que paró a cargar.
 *
 * Una vez que se tiene el grafo completo mencionado anteriormente, se construye otro grafo con las
 * siguientes características:
 * - Se crean 61 vértices a partir de cada vértice del grafo anterior.
 * - Cada vértice de los 61 representa las distintas formas de llenar el tanque desde esa ciudad.
 * - Cada uno de estos vértices es adyacente a todo el resto, excepto con su grupo de 61.
 *
 * Quedaron poco elegantes algunas partes que próximamente voy a pulir (dos implementaciones de
 * Bellman-Ford por ejemplo) pero al parecer funciona bien. Y en principio funcionaría también
 * con cualquier otro algoritmo de camino mínimo sin requerir modificaciones sustanciales.
 */

#ifndef GAS_GRAPH_H
#define GAS_GRAPH_H

#include <vector>
#include <istream>
#include "../utils/types.h"

using namespace std;

class GasGraph {
public:
    typedef struct s_Edge {
        uint destination; // vertex id
        ulong cost;

        s_Edge(uint destination, ulong cost) : destination(destination), cost(cost) {};
    } Edge;
    
    GasGraph(istream& istream, ulong tankCapacity);
    uint getVertices() const;
    uint getCities() const;
    const vector<Edge>& getNeighbors(uint vertex) const;
    uint getCity(uint vertex) const;
    uint getTankCapacity() const;
    uint getVertex(uint city, ulong gasCharge) const;

private:
    vector<vector<Edge>> adjacencyList;
    uint cities;
    const ulong tankCapacity;

    void addEdges(uint originCity, uint destinationCity, ulong gasRequired, ulong gasPrice1,
        ulong gasPrice2);
};

#endif
