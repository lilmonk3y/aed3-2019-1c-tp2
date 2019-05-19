#include <iostream>
#include <vector>
#include "../entity/GasGraph.h"
#include "gas-graph-bellman-ford.hpp"

using namespace std;

int main() {
  // Lectura de la entrada:

  GasGraph graph(cin);

  // Cálculo de caminos mínimos e impresión de la salida

  vector<ulong> min(graph.getCities()); // min[i][j] = peso del camino de i a j con peso mínimo
  for(uint originCity = 0; originCity < graph.getCities(); ++originCity) {
    bellmanFord::bellmanFord(graph, originCity, min);

    for (uint destCity = 0; destCity < graph.getCities(); ++destCity) {
      if (originCity == destCity) continue;
      cout << originCity << " " << destCity << " " << min[destCity] << endl;
    }
  }
  
  return 0;
}