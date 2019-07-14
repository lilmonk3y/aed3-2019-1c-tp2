### Ejemplo de generar grafos y medir tiempos

Generar 100 grafos para cada valor de n en [5, 100] saltando valores de 5 en 5 con densidad de aristas 0.4

Desde carpeta project

```
python3 project/src/experiments/minpath/gen_random_connected_graphs.py -g 100 -n 5 -N 100 -s 5 -d 0.4
./timer < ./project/src/experiments/minpath/salidas/salida_grafos_random_100_5_100_5_0.4.txt > ./project/src/experiments/minpath/salidas/tiempos_salida_grafos_random_100_5_100_5_0.4.csv

```

Para ver el mensaje de ayuda del generador de grafos ejecutarlo con el parámetro -h



### Ejemplo para correr el algoritmo de segmentación de imagenes (usar python2):

cd cmake-build-debug

cmake ..

make

echo "array 2000 0.8 ../fuentes_de_la_catedra/BSDS300/images/train/2092.jpg" | python2 ../project/src/experiments/segmentacion/sendImage.py | ./runSegmentacion | python2 ../project/src/experiments/segmentacion/pintar-segmentacion.py

El primer parámetro es el tipo de disjoinset esperado (array, tree, treeCompressed y arrayC), el segundo es el scale a utilizar y el tercero el valor para el filtro gausiano
Hay que poner donde dice 2000 el número que queramos desde 1 a 500000 es válido, y la ruta de la imagen deseada, variando ese número obtendremos diferentes segmentaciones.

### Paquetes usados (instalar con pip, en la terminal pip install nombrePaquete):
import cv2 (para python 2)  ###pip2 install opencv-python
import sys (para python 2)

numpy   (para python2)
matplotlib  (para python2)

### para usar python 3 debemos cambiar los raw_input() por input() y print "var" por print(var)
