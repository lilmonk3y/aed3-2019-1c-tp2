#!/usr/bin/python3
# -*- coding: utf-8 -*-

import sys
import networkx as nx
import random
import os

# Genera grafos con los vértices y la densidad indicada en el mensaje de ayuda.
# Ejecutar python gen_graphs.py sin parámetros para ver la ayuda.
# Las distancias entre ciudades se generan con valores en el intervalo [1, 60] y los costos de nafta
# en el intervalo [1, 10], ambos con distribución uniforme.

def escribirArchivoEnBytes(mensajeEnString, archivo):
  mensajeEnBytes = bytes(mensajeEnString, "utf-8")
  archivo.write(mensajeEnBytes)

def escribirGrafoRandom(n, p, archivoDeSalida, semilla):
  # Decide qué algoritmo usar de acuerdo a la densidad esperada del grafo
  gen_graph = nx.fast_gnp_random_graph if p < 2*n/(n-1) else nx.gnp_random_graph

  # Grafo de n nodos donde la probabilidad de que un eje exista es de p
  G = gen_graph(n, p, semilla)

  # Esto es re sucio, y puede tardar sobretodo con un p chico. Pero es fácil y se corre una vez :)
  while (not nx.is_connected(G)):
    G = gen_graph(n, p, semilla)
      
  # Agrega las distancias entre ciudades
  random.seed(semilla)
  for (vertex1, vertex2, edge_data) in G.edges(data=True):
    edge_data['weight'] = random.randint(1, 60)

  mensaje = f"{n} {G.number_of_edges()}\n" # número de vertices y de aristas
  
  # Agrega los costos de nafta de cada ciudad
  for i in range(0, n):
    costo_nafta = random.randint(1, 10)
    mensaje += f"{costo_nafta}\n"
   
  escribirArchivoEnBytes(mensaje, archivoDeSalida)
  nx.write_weighted_edgelist(G, archivoDeSalida)

if len(sys.argv) < 6:
  archivoActual = sys.argv[0]
  ayuda = (f"## Forma de uso: python {archivoActual} <cant_grafos> <n_inf> <n_sup> <n_saltar> <probabilidad_eje>"
          + " <ruta_archivo_salida> donde:\n"
          + "cant_grafos = cantidad de grafos a generar por cada número de vértices,\n"
          + "n_inf = número de vértices inferior,\n"
          + "n_sup = número de vértices superior,\n"
          + "n_saltar = número de vértices a saltar,\n"
          + "probabilidad_eje = probabilidad de que un eje exista,\n"
          + "ruta_archivo_salida = ruta al archivo de salida (opcional).")
  print(ayuda)
  sys.exit()

cantGrafosPorCadaN = int(sys.argv[1])
n_min = int(sys.argv[2])
n_max = int(sys.argv[3])
n_step = int(sys.argv[4])
p = float(sys.argv[5])
rutaDeArchivo = (sys.argv[6] if len(sys.argv) > 6
  else f"./salidas/salida_grafos_random_{cantGrafosPorCadaN}_{n_min}_{n_max}_{n_step}_{p}.csv")
valoresDeN = range(n_min, n_max + 1, n_step)
cantGrafos = len(valoresDeN) * cantGrafosPorCadaN
ruta = "/".join(rutaDeArchivo.split("/")[0:-1]) # ruta sin el nombre de archivo
os.makedirs(ruta, exist_ok=True)
semilla = 107
with open(rutaDeArchivo, "wb") as archivo:
  escribirArchivoEnBytes(f"{cantGrafos}\n", archivo)
  for n in valoresDeN:
    for i in range(0, cantGrafosPorCadaN + 1):
      escribirGrafoRandom(n, p, archivo, semilla)
      semilla += 1
    
print(f"Salida escrita en {rutaDeArchivo}") 
