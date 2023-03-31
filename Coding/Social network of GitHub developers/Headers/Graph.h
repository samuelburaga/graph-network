#pragma once
#include "../Headers/sparseMatrix.h"
#include <queue>
#include <vector>
#include <list>
#include <set>
#include <iostream>
#include <fstream>

template <class Type> 
class Graph
{
private:
	unsigned long long vertices, edges;
	std::list<Type>* adjacencyList;
	sparseMatrix <bool> adjacencyMatrix;
	sparseMatrix <bool> incidenceMatrix;
public:
	Graph();
	Graph(const unsigned long long&, unsigned long long edges = 0);
	void inputData();
	void addEdge(const unsigned long long&, const unsigned long long&);
	void addEdge(const unsigned long long&, const unsigned long long&, const unsigned long long&);
	unsigned long long& getVertices();
	template <class Type> friend std::ostream& operator<<(std::ostream&, Graph <Type>&);
	void printAdjacencyList();
	void printAdjacencyMatrix();
	void printIncidenceMatrix();
	bool BFS(const Type&, const Type&, Type[], unsigned long long[]);
	void printShortestDistance(const Type&, const Type&);
	void DFS(unsigned long long v, bool[], std::vector<Type>&);
	void countAndPrintConnectedComponents();
	void findMST();
};
template <class Type> Graph <Type>::Graph()
{
	(*this).vertices = (*this).edges = 0;
	(*this).adjacencyMatrix.num_rows = (*this).adjacencyMatrix.num_cols = 0;
	(*this).incidenceMatrix.num_rows = (*this).incidenceMatrix.num_cols = 0;
}
template <class Type> Graph <Type>::Graph(const unsigned long long& vertices, unsigned long long edges)
{
	(*this).vertices = vertices;
	adjacencyList = new std::list<Type>[(*this).vertices];
	(*this).adjacencyMatrix.getNumberOfRows() = (*this).adjacencyMatrix.getNumberOfColumns() = (*this).vertices;
	(*this).adjacencyMatrix.getNumberOfRows() = (*this).vertices;
	(*this).adjacencyMatrix.getNumberOfColumns() = (*this).edges;
}
template <class Type> unsigned long long& Graph <Type>::getVertices()
{
	return (*this).vertices;
}
template <class Type> void Graph <Type>::addEdge(const unsigned long long& u, const unsigned long long &v)
{
	//adjacencyList[u].push_back(v);
	(*this).adjacencyMatrix.add(u, v, true);
	(*this).adjacencyMatrix.add(v, u, true);
}
template <class Type> void Graph <Type>::addEdge(const unsigned long long& u, const unsigned long long& v, const unsigned long long& edge)
{
	adjacencyList[u].push_back(v);
	adjacencyList[v].push_back(u);
	(*this).adjacencyMatrix.add(u, v, true);
	(*this).adjacencyMatrix.add(v, u, true);
	(*this).incidenceMatrix.add(u, edge, true);
	(*this).incidenceMatrix.add(v, edge, true);
}
template <class Type> std::ostream& operator<<(std::ostream& output, Graph <Type>& graph)
{
	graph.printAdjacencyList();
	graph.printAdjacencyMatrix();
	graph.printIncidenceMatrix();
	return output;
}
template <class Type> void Graph <Type>::printAdjacencyList()
{
	std::ofstream file("D:/ULBS/Anul II/Semestrul II/Modulul 1/Algoritmica grafurilor/Project/Coding/Social network of GitHub developers/Output/Adjacency List.csv");
	for (unsigned long long vertex = 0; vertex < /*(*this).vertices*/ 50; vertex++)
	{
		file << vertex << ",";
		typename std::list<Type>::iterator i;
		for (i = adjacencyList[vertex].begin(); i != adjacencyList[vertex].end(); ++i)
		{
			file << *i;
			typename std::list<Type>::iterator j;
			j = i;
			j++;
			if (j != adjacencyList[vertex].end())
			{
				file << ",";
			}
		}
		file << "\n";
	}
	file.close();
}
template <class Type> void Graph <Type>::printAdjacencyMatrix()
{
	std::ofstream file("D:/ULBS/Anul II/Semestrul II/Modulul 1/Algoritmica grafurilor/Project/Coding/Social network of GitHub developers/Output/Adjacency Matrix.csv");
	for (unsigned long long row = 0; row < /*(*this).vertices*/50; row++)
	{
		for (unsigned long long column = 0; column < /*(*this).vertices */ 50; column++) 
		{
			file << (*this).adjacencyMatrix.get(row, column);
			if (column < /*(*this).vertices*/50 - 1)
			{
				file << ",";
			}
		}
		file << "\n";
	}
	file.close();
}
template <class Type> void Graph <Type>::printIncidenceMatrix()
{
	std::ofstream file("D:/ULBS/Anul II/Semestrul II/Modulul 1/Algoritmica grafurilor/Project/Coding/Social network of GitHub developers/Output/Incidence Matrix.csv");
	for (unsigned long long row = 0; row < /*(*this).vertices*/50; row++)
	{
		for (unsigned long long column = 0; column < /*(*this).vertices */ 50; column++)
		{
			file << (*this).incidenceMatrix.get(row, column);
			if (column < /*(*this).vertices*/50 - 1)
			{
				file << ",";
			}
		}
		file << "\n";
	}
	file.close();
}
template <class Type> bool Graph<Type>::BFS(const Type& source, const Type& destination,  Type predecessor[], unsigned long long distance[])
{
	// Create a queue for BFS
	std::queue<Type> queue;

	// Mark all the vertices as not visited and initialize predecessor and distance arrays
	bool* visited = new bool[vertices];
	for (unsigned long long i = 0; i < vertices; i++) 
	{
		visited[i] = false;
		predecessor[i] = -1;
		distance[i] = UINT_MAX;
	}

	// Mark the source vertex as visited and enqueue it
	visited[source] = true;
	distance[source] = 0;
	queue.push(source);

	// Loop until the queue is empty
	while (!queue.empty()) {
		// Dequeue a vertex from the queue
		Type currentVertex = queue.front();
		queue.pop();

		// Get all adjacent vertices of the dequeued vertex currentVertex
		for (auto it = adjacencyList[currentVertex].begin(); it != adjacencyList[currentVertex].end(); ++it) {
			// If an adjacent vertex has not been visited, then mark it visited and enqueue it
			if (!visited[*it]) {
				visited[*it] = true;
				distance[*it] = distance[currentVertex] + 1;
				predecessor[*it] = currentVertex;
				queue.push(*it);

				// If the destination vertex is found, return true
				if (*it == destination) {
					delete[] visited;
					return true;
				}
			}
		}
	}

	delete[] visited;

	// If destination vertex is not found, return false
	return false;
}
template <class Type> void Graph <Type>::printShortestDistance(const Type& source, const Type& destination)
{
	// Initialize predecessor and distance arrays
	Type* predecessor = new Type[vertices];
	unsigned long long* distance = new unsigned long long[vertices];

	// Run BFS and check if destination can be reached from source
	if (BFS(source, destination, predecessor, distance)) 
	{
		// Print the shortest distance and path
		std::cout << "The shortest distance between " << source << " and " << destination << " is " << distance[destination] << "." << std::endl;

		std::vector<Type> path;
		Type currentVertex = destination;
		path.push_back(currentVertex);
		while (predecessor[currentVertex] != -1) 
		{
			currentVertex = predecessor[currentVertex];
			path.push_back(currentVertex);
		}
		std::cout << "Shortest path is: ";
		for (typename std::vector<Type>::reverse_iterator it = path.rbegin(); it != path.rend(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << "." << std::endl;
	}
	else 
	{
		std::cout << "No path exists between " << source << " and " << destination << std::endl;
	}

	delete[] predecessor;
	delete[] distance;
}
template <class Type> void Graph<Type>::DFS(unsigned long long v, bool visited[], std::vector<Type>& component)
{
	visited[v] = true;
	component.push_back(v);

	typename std::list<Type>::iterator i;
	for (i = adjacencyList[v].begin(); i != adjacencyList[v].end(); ++i) {
		if (!visited[*i]) {
			DFS(*i, visited, component);
		}
	}
}
template <class Type> void Graph<Type>::countAndPrintConnectedComponents()
{
	bool* visited = new bool[vertices];
	for (unsigned long long i = 0; i < vertices; i++) {
		visited[i] = false;
	}

	unsigned long long numComponents = 0;
	for (unsigned long long i = 0; i < vertices; i++) {
		if (!visited[i]) {
			numComponents++;
			std::vector<Type> component;
			DFS(i, visited, component);
			std::cout << "Component " << numComponents << ": ";
			for (typename std::vector<Type>::iterator it = component.begin(); it != component.end(); ++it) {
				std::cout << *it << " ";
			}
			std::cout << std::endl;
		}
	}

	std::cout << "Number of connected components: " << numComponents << std::endl;

	delete[] visited;
}
template <class Type> void Graph<Type>::findMST() {
	// create a priority queue to hold edges in ascending order
	std::priority_queue<std::pair<int, std::pair<unsigned long long, unsigned long long>>,
		std::vector<std::pair<int, std::pair<unsigned long long, unsigned long long>>>> pq;

	// add all edges to the priority queue
	for (unsigned long long i = 0; i < vertices; i++) {
		for (typename std::list<Type>::iterator it = adjacencyList[i].begin(); it != adjacencyList[i].end(); ++it) {
			unsigned long long v = i;
			unsigned long long w = *it;
			if (v < w) {
				pq.push(std::make_pair(1, std::make_pair(v, w)));
			}
		}
	}

	// create a disjoint set for vertices
	std::vector<unsigned long long> parent(vertices);
	for (unsigned long long i = 0; i < vertices; i++) {
		parent[i] = i;
	}

	// create a vector to store the MST edges
	std::vector<std::pair<unsigned long long, unsigned long long>> mst;

	// process edges in the priority queue until all vertices are in the same component
	while (!pq.empty() && mst.size() < vertices - 1) {
		std::pair<int, std::pair<unsigned long long, unsigned long long>> curr = pq.top();
		pq.pop();
		unsigned long long u = curr.second.first;
		unsigned long long v = curr.second.second;

		// check if u and v are in different components
		while (parent[u] != u) {
			u = parent[u];
		}
		while (parent[v] != v) {
			v = parent[v];
		}
		if (u != v) {
			// add the edge to the MST
			mst.push_back(std::make_pair(curr.second.first, curr.second.second));
			parent[u] = v;
		}
	}

	// print the MST edges
	std::cout << "Minimum Spanning Tree:" << std::endl;
	for (typename std::vector<std::pair<unsigned long long, unsigned long long>>::iterator it = mst.begin(); it != mst.end(); ++it) {
		std::cout << it->first << " - " << it->second << std::endl;
	}
}
