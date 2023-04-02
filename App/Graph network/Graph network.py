import csv
import pandas as pd
import networkx as nx
import matplotlib.pyplot as plt
import random
import numpy as np

data = pd.read_csv("Resources/inf-power/inf-power.csv")
# print(data)

G = nx.Graph()
for index in range(4941):
    G.add_node(index + 1)
for index, row in data.iterrows():
    G.add_edge(row[0], row[1])
node_colors = {}
for node in G.nodes():
    node_colors[node] = "#" + ''.join([random.choice('0123456789ABCDEF') for j in range(6)])
nx.draw(G, with_labels = True, node_size = 400, node_color = list(node_colors.values()), font_size = 6)

adjacency_matrix = pd.DataFrame(nx.adjacency_matrix(G).todense())
adjacency_matrix.to_csv('Output/adjacency_matrix.csv', index = False, header = False)

incidence_matrix = nx.incidence_matrix(G, nodelist=None, edgelist=None, oriented=False, weight=None).todense()
df = pd.DataFrame(incidence_matrix, columns=[e for e in G.edges()])
df.insert(0, 'Node', [n for n in G.nodes()])
df.to_csv('Output/incidence_matrix.csv', index=False)

adjacency_list = nx.to_dict_of_lists(G)
with open('Output/adjacency_list.csv', 'w', newline='') as f:
    writer = csv.writer(f)
    writer.writerow(['Node', 'Neighbors'])
    for node, neighbors in adjacency_list.items():
        writer.writerow([node] + neighbors)
        
plt.show()