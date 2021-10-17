import networkx as nx
import numpy as np
import matplotlib.pyplot as plt
import csv

A = []
with open('weightsMatrixFromDataset.csv', 'r') as f:
    reader = csv.reader(f, delimiter=',')
    for r in reader:
        row = list(map(float, r))
        A.append(row)
A = np.array(A)
print(A)
print(A.shape)

G = nx.from_numpy_matrix(A)
print("Graph from dataset")
print(G)
nx.draw_circular(G, with_labels=False) # "with_labels=False" para deixar a imagem mais limpa
plt.savefig("GraphFromDataset.png", format="PNG")
plt.clf()

output = np.array([[0 for _ in range(500)] for _ in range(500)])
with open('outputFromDataset.csv', 'r') as r:
    reader = csv.reader(r, delimiter=',')
    reader = next(reader)
    for r in reader:
        if not r:
            continue
        u, v = map(int, r.split("-->"))
        output[u][v] = 1

outputGraph = nx.Graph(output)
print("Graph output")
print(outputGraph)
nx.draw_kamada_kawai(outputGraph, with_labels=False)
plt.savefig("GraphOutput.png", format="PNG")