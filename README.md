### Ejemplo de generar grafos y medir tiempos

Generar 100 grafos para cada valor de n en [5, 100] saltando valores de 5 en 5 con densidad de aristas 0.4

Desde carpeta project

```
python3 project/src/experiments/minpath/gen_random_connected_graphs.py -g 100 -n 5 -N 100 -s 5 -d 0.4
./timer < ./project/src/experiments/minpath/salidas/salida_grafos_random_100_5_100_5_0.4.txt > ./project/src/experiments/minpath/salidas/tiempos_salida_grafos_random_100_5_100_5_0.4.csv

```

Para ver el mensaje de ayuda del generador de grafos ejecutarlo con el parámetro -h
