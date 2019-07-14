edges_max = 0 
dist_max = 0
for dist in range(1, 61):
  edges = 0
  for initial_gas in range(0, 61):
    minimum_refill = dist - initial_gas if dist > initial_gas else 0
    edges += 61 - minimum_refill
  if edges > edges_max:
    edges_max = edges
    dist_max = dist
  print(f"Distancia: {dist}\tAristas: {edges}")

print(f"El máximo número de aristas es {edges_max} " + \
      f"con distancia {dist_max}")