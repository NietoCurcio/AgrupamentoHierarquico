import networkx as nx
import numpy as np
import matplotlib.pyplot as plt
import csv

A = []
with open('adjacencyMatrix.csv', 'r') as f:
    reader = csv.reader(f, delimiter=',')
    for r in reader:
        row = list(map(int, r))
        A.append(row)

A = np.array(A)
print(A)

G = nx.from_numpy_matrix(A)
nx.draw(G, with_labels=True)
plt.savefig("Graph.png", format="PNG")

output = np.array([[0 for _ in range(13)] for _ in range(13)])
with open('output.csv', 'r') as r:
    reader = csv.reader(r, delimiter=',')
    reader = next(reader)
    for r in reader:
        if not r:
            continue
        u, v = map(int, r.split("-->"))
        output[u][v] = 1

outputGraph = nx.Graph(output)
print(outputGraph)
nx.draw(outputGraph, with_labels=True)
plt.savefig("GraphOutput.png", format="PNG")