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

def print_graph(vertices, number_of_edges, output_file, distance_min, distance_max):
  number_of_vertices = len(vertices)
  print(f"{number_of_vertices} {number_of_edges}", file=output_file)
  for i in range(0, number_of_vertices):
    vertex_weight = random.randint(1, 20)
    print(vertex_weight, file=output_file)

  graph = random_connected_graph.random_walk(vertices, number_of_edges)

  for vertex1, vertex2 in graph.edges:
    distance = random.randint(distance_min, distance_max)
    print(f"{vertex1} {vertex2} {distance}", file=output_file)

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
  parser.add_argument('-f', '--output-file', help='(optional) output file'),
  parser.add_argument('-l', '--distance-min', type=int, default=1,
                      help='(optional) min number of distance range [l, L] - default=1'),
  parser.add_argument('-L', '--distance-max', type=int, default=60,
                      help='(optional) max number of distance range [l, L] - default=60')

  args = parser.parse_args()

  if args.n_max is None:
    args.n_max = args.n_min

  if args.output_file is None:
    args.output_file = ("./salidas/salida_grafos_random_" +
                f"{args.graphs}_{args.n_min}_{args.n_max}_{args.step}_{args.density}.txt")

  path = "/".join(args.output_file.split("/")[0:-1]) # path without file name
  os.makedirs(path, exist_ok=True)

  n_values = range(args.n_min, args.n_max+1, args.step)
  with open(args.output_file, "w") as output_file:
    print(len(n_values)*args.graphs, file=output_file)
    for n in n_values:
      edges_max = n*(n-1)/2
      edges_min = n-1
      edges = int(edges_max*args.density) # number of edges
      if edges < edges_min:
        new_density = edges_min/edges_max
        print((f"Expected number of edges with nodes={n} and density="
          + f"{args.density} is {edges} which would result in an unconnected "
          + f"graph. New density={new_density:.2f}, edges={edges_min}\n"))
        edges = edges_min
      vertices = list(range(n))
      for i in range(0, args.graphs):
        print_graph(vertices, edges, output_file, args.distance_min, args.distance_max)






