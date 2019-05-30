#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include "../../../src/parteUno/SegmentationAlgorithm.h"
#include "../../../src/utils/DisjoinSet.h"
#include "../../../src/utils/ArrayDisjoinSet.h"
#include "../../../src/utils/TreeCompressedDisjoinSet.h"
#include "../../../src/utils/ArrayCompressedDisjoinSet.h"
#include "../../../src/utils/TreeDisjoinSet.h"

using namespace std;

// funcion en comun de los experimentos si se quiere usar: (corre el algoritmo y ademas mide tiempos y genera output con imagen segmentada)
void correrAlgoritmoYGenerarOutputs (vector<vector<int> > imagen,int segmentationScale,int ancho,int alto,DisjoinSet* disjoinSet,string fileOutputName,string fileOutputTimesName) {
    // contar el tiempo:
    std::ofstream fileExperimento;
    fileExperimento.open(fileOutputTimesName,std::ios::out);
    std::chrono::steady_clock::time_point tiempoInicio = std::chrono::steady_clock::now();
    // seteo toda la configuracion al segmentationAlgorithm
    SegmentationAlgorithm* segmentationAlgorithm = new SegmentationAlgorithm(imagen, segmentationScale, ancho, alto,disjoinSet);
    // ejecuto el segmentation algorithm:
    vector<vector<int> > imagenSegmentada = segmentationAlgorithm->imageToSegmentation();
    std::chrono::steady_clock::time_point tiempoFinal = std::chrono::steady_clock::now();
    std::chrono::duration<double> tiempo = std::chrono::duration_cast<std::chrono::duration<double > >(tiempoFinal - tiempoInicio); // diferencia tiempos
    fileExperimento << std::fixed << tiempo.count()  << "\n"; // mando el tiempo al file, con notacion con coma, osea no cientifica
    fileExperimento.close();
    // genero la imagen segmentada en el file output
    segmentationAlgorithm->generarFileOutput(imagenSegmentada,ancho, alto,fileOutputName); // genera el file
}

void correrExperimento1() {
    vector<vector<int> > imagen = {{248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,189,103,34,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,189,103,34,248,248,248},
                                   {248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,232,121,36,0,0,0,248,248,248,248,248,248,248,248,248,248,248,248,248,232,121,36,0,0,0,248,248,248},
                                   {248,248,248,248,248,248,248,248,248,248,248,248,248,248,232,110,17,0,0,0,0,0,248,248,248,248,248,248,248,248,248,248,248,232,110,17,0,0,0,0,0,248,248,248},
                                   {248,248,248,248,248,248,248,248,248,248,248,248,248,147,19,0,0,0,0,0,0,0,248,248,248,248,248,248,248,248,248,248,147,19,0,0,0,0,0,0,0,248,248,248},
                                   {248,248,248,248,248,248,248,248,248,248,248,227,65,0,0,0,0,0,0,12,87,189,248,248,248,248,248,248,248,248,227,65,0,0,0,0,0,0,12,87,189,248,248,248},
                                   {248,248,248,248,248,248,248,248,248,248,195,28,0,0,0,0,0,0,72,215,248,248,248,248,248,248,248,248,248,195,28,0,0,0,0,0,0,72,215,248,248,248,248,248},
                                   {248,248,248,248,248,248,248,248,248,195,17,0,0,0,0,0,6,137,248,248,248,248,248,248,248,248,248,248,195,17,0,0,0,0,0,6,137,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,248,248,248,207,19,0,0,0,0,0,6,159,248,248,248,248,248,248,248,248,248,248,207,19,0,0,0,0,0,6,159,248,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,248,248,238,43,0,0,0,0,0,0,121,248,248,248,248,248,248,248,248,248,248,238,43,0,0,0,0,0,0,121,248,248,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,248,248,110,0,0,0,0,0,0,36,242,248,248,248,248,248,248,248,248,248,248,110,0,0,0,0,0,0,36,242,248,248,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,248,215,6,0,0,0,0,0,0,137,248,248,248,248,248,248,248,248,248,248,215,6,0,0,0,0,0,0,137,248,248,248,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,248,94,0,0,0,0,0,0,0,215,248,248,248,248,248,248,248,248,248,248,94,0,0,0,0,0,0,0,215,248,248,248,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,238,17,0,0,0,0,0,0,0,238,248,248,248,248,248,248,248,248,248,238,17,0,0,0,0,0,0,0,238,248,248,248,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,177,0,0,0,0,0,0,0,0,177,248,248,248,248,248,248,248,248,248,177,0,0,0,0,0,0,0,0,177,248,248,248,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,113,0,0,0,0,0,0,0,0,24,195,248,248,248,248,248,248,248,248,113,0,0,0,0,0,0,0,0,24,195,248,248,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,58,0,0,0,0,0,0,0,0,0,6,113,242,248,248,248,248,248,248,58,0,0,0,0,0,0,0,0,0,6,113,242,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,36,0,0,0,0,0,0,0,0,0,0,0,43,215,248,248,248,248,248,36,0,0,0,0,0,0,0,0,0,0,0,43,215,248,248,248,248,248,248},
                                   {248,248,248,248,248,19,0,0,0,0,0,0,0,0,0,0,0,0,36,238,248,248,248,248,19,0,0,0,0,0,0,0,0,0,0,0,0,36,238,248,248,248,248,248},
                                   {248,248,248,248,248,6,0,0,0,0,0,0,0,0,0,0,0,0,0,121,248,248,248,248,6,0,0,0,0,0,0,0,0,0,0,0,0,0,121,248,248,248,248,248},
                                   {248,248,248,248,248,19,0,0,0,0,0,0,0,0,0,0,0,0,0,43,248,248,248,248,19,0,0,0,0,0,0,0,0,0,0,0,0,0,43,248,248,248,248,248},
                                   {248,248,248,248,248,43,0,0,0,0,0,0,0,0,0,0,0,0,0,17,248,248,248,248,43,0,0,0,0,0,0,0,0,0,0,0,0,0,17,248,248,248,248,248},
                                   {248,248,248,248,248,110,0,0,0,0,0,0,0,0,0,0,0,0,0,12,248,248,248,248,110,0,0,0,0,0,0,0,0,0,0,0,0,0,12,248,248,248,248,248},
                                   {248,248,248,248,248,207,6,0,0,0,0,0,0,0,0,0,0,0,0,36,248,248,248,248,207,6,0,0,0,0,0,0,0,0,0,0,0,0,36,248,248,248,248,248},
                                   {248,248,248,248,248,248,103,0,0,0,0,0,0,0,0,0,0,0,0,113,248,248,248,248,248,103,0,0,0,0,0,0,0,0,0,0,0,0,113,248,248,248,248,248},
                                   {248,248,248,248,248,248,242,65,0,0,0,0,0,0,0,0,0,0,28,232,248,248,248,248,248,242,65,0,0,0,0,0,0,0,0,0,0,28,232,248,248,248,248,248},
                                   {248,248,248,248,248,248,248,242,103,6,0,0,0,0,0,0,0,36,207,248,248,248,248,248,248,248,242,103,6,0,0,0,0,0,0,0,36,207,248,248,248,248,248,248},
                                   {248,248,248,248,248,248,248,248,248,215,103,43,17,6,24,65,147,242,248,248,248,248,248,248,248,248,248,248,215,103,43,17,6,24,65,147,242,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248},
                                   {248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248,248}};

    // configuraciones:
    int ancho = 44; // ancho de la imagen
    int alto = 33; // alto de la imagen
    int segmentationScale = 900; // tamaño promedio de las componentes (en cantidad de pixeles)
    string fileOutputName = "experimento1-imagen-segmentada";
    string fileOutputTimesName = "experimento1-imagen-segmentada-tiempo";
    DisjoinSet* disjoinSet = new ArrayDisjoinSet();//new ArrayCompressedDisjoinSet(); // estrategia usada del disjoint set

    // ejecuto el algoritmo y genero los 2 files de salida con la imagen segmentada y el tiempo que tardo
    correrAlgoritmoYGenerarOutputs(imagen,segmentationScale,ancho,alto,disjoinSet,fileOutputName,fileOutputTimesName);
}








void correrExperimento2() {
    vector<vector<int> > imagen = {};

    // configuraciones:
    int ancho = 0; // ancho de la imagen
    int alto = 0; // alto de la imagen
    int segmentationScale = 0; // tamaño promedio de las componentes (en cantidad de pixeles)
    string fileOutputName = "experimento2-imagen-segmentada";
    string fileOutputTimesName = "experimento2-imagen-segmentada-tiempo";
    DisjoinSet* disjoinSet = new ArrayDisjoinSet();//new ArrayCompressedDisjoinSet(); // estrategia usada del disjoint set

    // ejecuto el algoritmo y genero los 2 files de salida con la imagen segmentada y el tiempo que tardo
    correrAlgoritmoYGenerarOutputs(imagen,segmentationScale,ancho,alto,disjoinSet,fileOutputName,fileOutputTimesName);
}

int main(){
    correrExperimento1(); // ArrayDisjoinSet, 33x44 pixeles, 3 componentes a simple vista, segmentationScale = 900
    //correrExperimento2(); // experiemento vacio
}

