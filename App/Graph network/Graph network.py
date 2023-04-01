import csv
import pandas as pd
import networkx as nx
import matplotlib.pyplot as plt
import random

data = pd.read_csv("Resources/lasftm_asia/lastfm_asia_edges.csv")
# print(data)
G = nx.Graph()
i = 1
for index, row in data.iterrows():
    G.add_edge(row['node_1'], row['node_2'])
    if  i > 50:
        break
    i = i + 1
# Draw the graph with the random node colors
node_colors = {}
for node in G.nodes():
    node_colors[node] = "#" + ''.join([random.choice('0123456789ABCDEF') for j in range(6)])
nx.draw(G, with_labels = True, node_color = list(node_colors.values()))
# nx.draw_spring(G, with_labels = True, node_size = 400)
plt.show()
