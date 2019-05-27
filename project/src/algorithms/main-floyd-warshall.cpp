#include <iostream>
#include <vector>
#include "../entity/GasGraph.h"
#include "floyd-warshall.hpp"


using namespace std;

int main() {//Todo: Cambiar el main de bellman para evitar main duplicado
  // Lectura de la entrada:
  GasGraph graph(cin);

  // Cálculo de caminos mínimos e impresión de la salida
  vector< vector<ulong> > D;  //Matriz de pesos
  vector< vector<ulong> > R; //Matríz de resultado
  floydWarshall(graph, D, R);

  for(uint i = 0; i < R.size(); ++i){
  	for(uint j = 0; j < R[i].size(); ++j){
  		if(i == j) continue;
  		cout << i << " " << j << " " << R[i][j] << " ";
  		cout << endl;
  	}
  }

/*  cout << "Todos los caminos: " << endl;
  for(uint i = 0; i < D.size(); ++i){
  	for(uint j = 0; j < D[i].size(); ++j){
  		if(i == j) continue;
  		cout << i << " " << j << " " << D[i][j] << " ";
  		cout << endl;
  	}
  }
*/
  return 0;
}