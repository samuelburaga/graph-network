import csv
import pandas as pd
import networkx as nx
import matplotlib.pyplot as plt
import random
import numpy as np

data = pd.read_csv("Resources/lasftm_asia/lastfm_asia_edges.csv")
G = nx.Graph()
for index in range(7624):
    G.add_node(index)
for index, row in data.iterrows():
    G.add_edge(row['node_1'], row['node_2'])
node_colors = {}
for node in G.nodes():
    node_colors[node] = "#" + ''.join([random.choice('0123456789ABCDEF') for j in range(6)])
nx.draw(G, with_labels = True, node_size = 400, node_color = list(node_colors.values()), font_size = 6)

# print(nx.adjacency_matrix(G))
# Get the adjacency matrix as a pandas DataFrame
adjacency_matrix = pd.DataFrame(nx.adjacency_matrix(G).todense())

# Export the adjacency matrix to a CSV file
adjacency_matrix.to_csv('Output/adjacency_matrix.csv', index = False, header = False)

plt.show()