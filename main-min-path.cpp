#include <iostream>
#include <vector>
#include "project/src/entity/GasGraph.h"
#include "project/src/algorithms/dijkstra-with-fifo-queue.hpp"
#include "project/src/algorithms/dijkstra-with-priority-queue.hpp"
#include "project/src/algorithms/floyd-warshall.hpp"
#include "project/src/algorithms/bellman-ford.hpp"

using namespace std;

#define TANK_CAPACITY 60
#define INITIAL_GAS_CHARGE 0
#define FINAL_GAS_CHARGE 0

typedef void f_minCostOneToMany_t (const GasGraph&, uint, vector<ulong>&, ulong, ulong);

int main(int argc, char* argv[]) {
  // Terminal parameters:

  if (argc < 2) {
    error:
    cout << "You must indicate the algorithm with options {df, dp, bf, fw} where:" << endl
         << "df=Dijkstra with FIFO queue;" << endl
         << "dp=Dijkstra with priority queue;" << endl
         << "bf=Bellman-Ford;" << endl
         << "fw=Floyd-Warshall." << endl
         << "Example: ./" << string(argv[0]) << " df" << endl;
    return 1;
  }
  string algorithm = string(argv[1]);

  // Read standard input:

  GasGraph graph(cin, TANK_CAPACITY);

  // Calculate minimum cost and print output

  if (algorithm == "df" || algorithm == "dp" || algorithm == "bf") {
    // One-to-many algorithms:

    vector<ulong> min;
    f_minCostOneToMany_t* f_algorithm;
    if (algorithm == "df") f_algorithm = dijkstraFifoQueue;
    else if (algorithm == "dp") f_algorithm = dijkstraPriorityQueue;
    else if (algorithm == "bf") f_algorithm = bellmanFord;

    for(uint originCity = 0; originCity < graph.getCities(); ++originCity) {
      f_algorithm(graph, originCity, min, INITIAL_GAS_CHARGE, FINAL_GAS_CHARGE);

      for (uint destCity = 0; destCity < graph.getCities(); ++destCity) {
        cout << originCity << " " << destCity << " " << min[destCity] << endl;
      }
    }
  } else if (algorithm == "fw") {
    // Many-to-many algorithms:

    vector<vector<ulong>> minCost; // Matriz de resultado
    floydWarshall(graph, minCost, INITIAL_GAS_CHARGE, FINAL_GAS_CHARGE);
    for (uint originCity = 0; originCity < graph.getCities(); ++originCity) {
      for (uint destCity = 0; destCity < graph.getCities(); ++destCity) {
        cout << originCity << " " << destCity << " " << minCost[originCity][destCity] << endl;
      }
    }
  } else {
    cerr << "The parameter does not match any supported algorithm." << endl;
    goto error;
  }

  return 0;
}