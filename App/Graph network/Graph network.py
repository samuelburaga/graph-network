import csv
import pandas as pd
import networkx as nx
import matplotlib.pyplot as plt
data = pd.read_csv("Resources/lasftm_asia/lastfm_asia_edges.csv")
print(data)
G = nx.Graph()
for index, row in data.iterrows():
    G.add_edge(row['node_1'], row['node_2'])
nx.draw_spring(G, with_labels = True, node_size = 400)
plt.show()
