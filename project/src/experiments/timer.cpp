#include <iostream>
#include <vector>
#include <cstdlib>
#include "../entity/GasGraph.h"
#include "../algorithms/dijkstra-with-fifo-queue.hpp"
#include "../algorithms/dijkstra-with-priority-queue.hpp"
#include "../algorithms/floyd-warshall.hpp"
#include "../algorithms/bellman-ford.hpp"
#include <chrono>

int main(int argc, char const* argv[]) {
  int numberOfRuns = argc < 2 ? 10 : stoi(argv[1]),
      numberOfGraphs;

  cin >> numberOfGraphs;
  cout << "n,m,bf,fw,dp,df" << endl;

  vector<vector<ulong>> minCost;

  for (int j = 0; j < numberOfGraphs; ++j) {
    GasGraph graph(cin, TANK_CAPACITY);

    for (int i = 0; i < numberOfRuns; ++i) {
      chrono::steady_clock::time_point begin, end;

      begin = chrono::steady_clock::now();
      fullBellmanFord(graph, minCost, INITIAL_GAS_CHARGE, FINAL_GAS_CHARGE);
      end = chrono::steady_clock::now(); 
      double time_bf = chrono::duration<double, milli>(end - begin).count();

      begin = chrono::steady_clock::now();
      floydWarshall(graph, minCost, INITIAL_GAS_CHARGE, FINAL_GAS_CHARGE);
      end = chrono::steady_clock::now(); 
      double time_fw = chrono::duration<double, milli>(end - begin).count();

      begin = chrono::steady_clock::now();
      fullDijkstraPriorityQueue(graph, minCost, INITIAL_GAS_CHARGE, FINAL_GAS_CHARGE);
      end = chrono::steady_clock::now(); 
      double time_dp = chrono::duration<double, milli>(end - begin).count();

      begin = chrono::steady_clock::now();
      fullDijkstraFifoQueue(graph, minCost, INITIAL_GAS_CHARGE, FINAL_GAS_CHARGE);
      end = chrono::steady_clock::now(); 
      double time_df = chrono::duration<double, milli>(end - begin).count();


      cout << graph.getCities() << "," << graph.getRoutes() << "," 
           << time_bf << "," << time_fw << "," << time_dp << "," << time_df << endl;
    }
  }

  return EXIT_SUCCESS;
}
  