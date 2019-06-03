#include <iostream>
#include <vector>
#include "project/src/parteUno/SegmentationAlgorithm.h"

DisjoinSet *selectStrategy(string basic_string);

using namespace std;

vector<vector<int>> getImagePixelsFromInput(int h, int w);

int main(){
     /*
     La entrada consistiŕa de una primera ĺınea con dos enteros w y h,
     que representan el ancho y el alto de la imagen a procesar.
     Luego les sucedeŕan h ĺıneas, cada una con w números enteros entre 0 y 255
     que representan la intensidad de los ṕıxeles de la imagen, consideŕandola como una imagen en escala de grises.
     La salida consistiŕa de h ĺıneas.
     Cada linea debeŕa contener w enteros.
     Dicho entero representar ́a el conjunto al que pertenece el pixel.
     */
    string strategyName;
    int scale;
    int h;
    int w;


    std::cin >> strategyName;
    std::cin >> scale;
    std::cin >> h; // altura
    std::cin >> w; // ancho

    // h lineas con w numeros enteros (pixel) entre 0 y 255:
    vector<vector<int> > image = getImagePixelsFromInput(h, w);


    
    SegmentationAlgorithm* algoritmo = new SegmentationAlgorithm(image, scale,w,h,strategyName); // configuracion algoritmo
    vector<vector<int> > imagenSegmentada = algoritmo->imageToSegmentation(); // llamda al algoritmo






    cout << h << endl;
    cout << w << endl;

    for(int fila = 0; fila < h ; fila ++) {
        for(int columna = 0; columna < w ; columna ++) {
            cout << imagenSegmentada[fila][columna] << endl;

        }
    }

}


vector<vector<int>> getImagePixelsFromInput(int h, int w){
    // h lineas con w numeros enteros (pixel) entre 0 y 255:
    vector<vector<int> > image;
    for(int linea = 0; linea < h ; linea ++) {
        vector<int> fila;
        for(int pixel = 0; pixel < w ; pixel ++) { // valores de grises de cada pixel
            int intensidadGris;
            std::cin >> intensidadGris; // valor entre 0 y 255
            if(0>intensidadGris || intensidadGris>255) {
                std::cout << "Hay un valor de un pixel que no esta entre 0 y 255" << std::endl;
                break;
            }
            fila.push_back(intensidadGris);
        }

        image.push_back(fila);
    }
    return image;
}
