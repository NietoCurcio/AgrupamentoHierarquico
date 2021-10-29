import networkx as nx
import numpy as np
import matplotlib.pyplot as plt
import csv
import argparse

parser = argparse.ArgumentParser(description='Graph Visualizer')
parser.add_argument('-v','--verbose', help='Show weights in graph from adjacency matrix [y]', required=False)
args = parser.parse_args()

A = []
with open('weightsMatrix.csv', 'r') as f:
    reader = csv.reader(f, delimiter=',')
    for r in reader:
        row = list(map(int, r))
        A.append(row)

A = np.array(A)
print(A)
print(A.shape)

G = nx.from_numpy_matrix(A)
# for i in range(A.shape[0]):
#     for j in range(A.shape[0]):
#         if i != j:
#             G.edges[i, j]['weight'] = A[i][j]

G.edges[0,1]['weight'] = 5
G.edges[0,2]['weight'] = 10
G.edges[1,2]['weight'] = 15


print(G.edges(data=True))

print("Graph inserted")
print(G)
fig = plt.figure(figsize=(3, 3))
nx.draw(G, with_labels=True)
if(args.verbose == 'y'):
    labels = nx.get_edge_attributes(G,'weight')
    print(labels)
    nx.draw_networkx_edge_labels(G, pos=nx.spring_layout(G), edge_labels=labels)
plt.savefig("Graph.png", format="PNG")
plt.clf()

output = np.array([[0 for _ in range(A.shape[0])] for _ in range(A.shape[0])])
with open('output.csv', 'r') as r:
    reader, = csv.reader(r, delimiter=',')
    # print(reader)
    for r in reader:
        if not r:
            continue
        u, v = map(int, r.split("-->"))
        output[u][v] = 1
        output[v][u] = 1
        
outputGraph = nx.Graph(output)
print("Graph output from dataset")
print(outputGraph)
fig = plt.figure(figsize=(3, 3))
nx.draw(outputGraph, with_labels=True)
plt.savefig("GraphOutput.png", format="PNG")