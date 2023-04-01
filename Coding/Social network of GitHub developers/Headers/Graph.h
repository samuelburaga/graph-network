#pragma once
#include "../Headers/sparseMatrix.h"
#include <queue>
#include <stack>
#include <vector>
#include <list>
#include <set>
#include <iostream>
#include <fstream>
#include <unordered_map>

template <class Type> 
class Graph
{
private:
	unsigned long long vertices, edges, numberOfComponents;
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
	unsigned long long countAndPrintConnectedComponents();
	bool isConnected();
	bool isEulerian();
	void printEulerianCycles();
};
template <class Type> Graph <Type>::Graph()
{
	(*this).vertices = (*this).edges = 0;
	(*this).numberOfComponents = 0;
	(*this).adjacencyMatrix.num_rows = (*this).adjacencyMatrix.num_cols = 0;
	(*this).incidenceMatrix.num_rows = (*this).incidenceMatrix.num_cols = 0;
}
template <class Type> Graph <Type>::Graph(const unsigned long long& vertices, unsigned long long edges)
{
	(*this).vertices = vertices;
	(*this).numberOfComponents = 0;
	(*this).adjacencyList = new std::list<Type>[(*this).vertices];
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
	static unsigned long long i = 1;
	std::cout << i << "\n";
	i++;
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
{/*
	visited[v] = true;
	component.push_back(v);
	typename std::list<Type>::iterator it;
	for (it = adjacencyList[v].begin(); it != adjacencyList[v].end(); ++it) 
	{
		if (!visited[*it]) 
		{
			DFS(*it, visited, component);
		}
	}*/
	std::stack<unsigned long long> stack;
	stack.push(v);

	while (!stack.empty()) {
		unsigned long long current = stack.top();
		stack.pop();

		if (!visited[current]) {
			visited[current] = true;
			component.push_back(current);

			for (auto i = adjacencyList[current].begin(); i != adjacencyList[current].end(); ++i) {
				if (!visited[*i]) {
					stack.push(*i);
				}
			}
		}
	}
}
template <class Type> unsigned long long Graph<Type>::countAndPrintConnectedComponents()
{
	std::ofstream file("D:/ULBS/Anul II/Semestrul II/Modulul 1/Algoritmica grafurilor/Project/Coding/Social network of GitHub developers/Output/Connected components.csv");
	bool* visited = new bool[(*this).vertices];
	for (unsigned long long index = 0; index < (*this).vertices; index++) 
	{
		visited[index] = false;
	}
	for (unsigned long long index = 0; index < (*this).vertices; index++) 
	{
		if (!visited[index]) 
		{
			(*this).numberOfComponents++;
			std::vector<Type> component;
			DFS(index, visited, component);
			file << "Component " << (*this).numberOfComponents << ", ";
			for (typename std::vector<Type>::iterator it = component.begin(); it != component.end(); ++it) 
			{
				file << *it << ", ";
			}
			file << "\n";
		}
	}
	file << "Number of connected components: " << (*this).numberOfComponents << std::endl;

	delete[] visited;
	return (*this).numberOfComponents;
}
template <class Type> bool Graph<Type>::isConnected()
{
	bool* visited = new bool[(*this).vertices];
	for (unsigned long long i = 0; i < (*this).vertices; i++) {
		visited[i] = false;
	}

	// Perform a DFS from the first vertex
	std::vector<Type> component;
	DFS(0, visited, component);

	// Check if all vertices were visited
	for (unsigned long long i = 0; i < (*this).vertices; i++)
	{
		if (!visited[i])
		{
			delete[] visited;
			return false;
		}
	}

	delete[] visited;
	return true;
}
template <class Type> bool Graph<Type>::isEulerian() 
{
	if (!(*this).isConnected()) 
	{  // check if the graph is not connected
		return false;
	}
	for (unsigned long long i = 0; i < (*this).vertices; i++)
	{
		if ((*this).adjacencyList[i].size() % 2 != 0) {  // check if any vertex has odd degree
			return false;
		}
	}
	return true;
}
template <class Type> void Graph<Type>::printEulerianCycles()
{
	if (!isEulerian()) 
	{
		std::cout << "The graph is not Eulerian.\n";
		return;
	}
	std::ofstream file("D:/ULBS/Anul II/Semestrul II/Modulul 1/Algoritmica grafurilor/Project/Coding/Social network of GitHub developers/Output/Eulerian Cycles.csv");
	std::vector<unsigned long long> circuit, nodes;
	circuit.reserve(edges);
	nodes.reserve(vertices);
	nodes.push_back(0);
	while (!nodes.empty()) 
	{
		unsigned long long node = nodes.back();
		if ((*this).adjacencyList[node].empty()) 
		{
			for (auto u : circuit) 
			{
				file << u << " -> ";
				file << u << ",";
			}
			fle << node << "\n";
			circuit.pop_back();
			nodes.pop_back();
			continue;
		}
		circuit.push_back(node);
		auto edge = (*this).adjacencyList[node].begin();
		nodes.push_back(*edge);
		(*this).adjacencyList[node].erase(edge);
	}
}

