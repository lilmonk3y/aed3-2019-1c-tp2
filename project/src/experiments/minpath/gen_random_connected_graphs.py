#!/usr/bin/python3
# -*- coding: utf-8 -*-

import random
import os
import argparse
import random_connected_graph

# Genera grafos con los vértices y la densidad indicada en el mensaje de ayuda.
# Ejecutar python gen_random_connected_graphss.py -h para ver la ayuda.
# Las distancias entre ciudades se generan con valores en el intervalo [1, 60] y los costos de nafta
# en el intervalo [1, 10], ambos con distribución uniforme.

def print_graph(number_of_vertices, number_of_edges):
  print(f"{number_of_vertices} {number_of_edges}")
  for i in range(0, number_of_vertices):
    vertex_weight = random.randint(1, 60)
    print(vertex_weight)

  graph = random_connected_graph.random_walk(number_of_vertices, number_of_edges)

  for vertex1, vertex2 in graph.edges:
    distance = random.randint(1, 10)
    print(f"{vertex1} {vertex2} {distance}")

if __name__ == '__main__':
  parser = argparse.ArgumentParser(description=__doc__)
  parser.add_argument('-g', '--graphs', type=int, required=True,
                      help='(required) number of graphs to generate for each number of vertices'),
  parser.add_argument('-n', '--n-min', type=int, required=True,
                      help='(required) min number of vertices range [n, N]'),
  parser.add_argument('-N', '--n-max', type=int,
                      help='(optional) max number of vertices range [n, N]'),
  parser.add_argument('-s', '--step', type=int, default=1,
                      help='(optional) step between values of [n, N] - default=1'),
  parser.add_argument('-d', '--density', type=float,
                      help='(required) density of edges, positive float <= 1'),
  parser.add_argument('-f', '--output-file', help='(optional) output file')

  args = parser.parse_args()

  if args.n_max is None:
    args.n_max = args.n_min

  if args.file is None:
    args.file = ("./salidas/salida_grafos_random_" +
                f"{args.graphs}_{args.n_min}_{args.n_max}_{args.step}_{args.density}.csv")

  path = "/".join(args.file.split("/")[0:-1]) # path without file name
  os.makedirs(path, exist_ok=True)

  # max number of edges for each value of n
  if args.n_min <= 2:
    n_max = args.n_min - 1
  else:
    m_max = (args.n_min - 1) * (args.n_min - 2) / 2 # combinatorial(n_min-1, 2)

  for n in range(args.n_min, args.n_max+1, args.step):
    m_max += n # combinatorial(n, 2)
    m = int(m_max*args.density) # number of edges
    for i in range(0, args.graphs+1):
      print_graph(n, m)






