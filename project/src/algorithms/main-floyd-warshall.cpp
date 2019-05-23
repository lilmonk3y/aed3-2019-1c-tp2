#include <iostream>
#include <vector>
#include "../entity/GasGraph.h"
#include "floyd-warshall.hpp"

int mainFloyd() {//Todo: Cambiar el main de bellman para evitar main duplicado
  // Lectura de la entrada:
  GasGraph graph(cin);

  // Cálculo de caminos mínimos e impresión de la salida
  vector< vector<ulong> > D(graph.getVertices(), vector<ulong>(graph.getVertices(), infty));  //Matriz de pesos
  floydWarshall(graph, D);
  for(uint i = 0; i < D.size(); ++i){
  	for(uint j = 0; j < D[i].size(); ++j){
  		if(i == j) continue;
  		cout << D[i][j] << " ";
  		cout << endl;
  	}
  }
}