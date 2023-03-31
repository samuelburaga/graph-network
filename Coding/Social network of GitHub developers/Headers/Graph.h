#pragma once
#include <queue>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>

template <class Type> 
class Graph
{
private:
	unsigned long long vertices;
	std::list<Type>* adjacencyList;
	bool** adjacencyMatrix;
	bool** incidenceMatrix;
public:
	Graph();
	Graph(const unsigned long long&);
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
};
template <class Type> Graph <Type>::Graph()
{
	(*this).vertices = 0;
	(*this).adjacencyMatrix = new bool* [0];
	(*this).incidenceMatrix = new bool* [0];
}
template <class Type> Graph <Type>::Graph(const unsigned long long& vertices)
{
	(*this).vertices = vertices;
	adjacencyList = new std::list<Type>[(*this).vertices];
	(*this).adjacencyMatrix = new bool* [(*this).vertices];
	for (unsigned long long index = 0; index < (*this).vertices; index++)
	{
		adjacencyMatrix[index] = new bool[(*this).vertices];
	}
	for (unsigned long long row = 0; row < (*this).vertices; row++)
	{
		for (unsigned long long column = 0; column < (*this).vertices; column++)
		{
			(*this).adjacencyMatrix[row][column] = false;
		}
	}
	(*this).incidenceMatrix = new bool* [(*this).vertices];
	for (unsigned long long index = 0; index < (*this).vertices; index++)
	{
		incidenceMatrix[index] = new bool[(*this).vertices];
	}
	for (unsigned long long row = 0; row < (*this).vertices; row++)
	{
		for (unsigned long long column = 0; column < (*this).vertices; column++)
		{
			(*this).incidenceMatrix[row][column] = false;
		}
	}
}
template <class Type> unsigned long long& Graph <Type>::getVertices()
{
	return (*this).vertices;
}
template <class Type> void Graph <Type>::addEdge(const unsigned long long& u, const unsigned long long &v)
{
	adjacencyList[u].push_back(v);
	adjacencyMatrix[u][v] = adjacencyMatrix[v][u] = true;
}
template <class Type> void Graph <Type>::addEdge(const unsigned long long& u, const unsigned long long& v, const unsigned long long& edge)
{
	adjacencyList[u].push_back(v);
	adjacencyMatrix[u][v] = adjacencyMatrix[v][u] = true;
	incidenceMatrix[u][edge] = incidenceMatrix[v][edge] = true;
}
template <class Type> std::ostream& operator<<(std::ostream& output, Graph <Type>& graph)
{
	//graph.printAdjacencyList();
	//graph.printAdjacencyMatrix();
	graph.printIncidenceMatrix();
	return output;
}
template <class Type> void Graph <Type>::printAdjacencyList()
{
	std::ofstream file("D:/ULBS/Anul II/Semestrul II/Modulul 1/Algoritmica grafurilor/Project/Coding/Social network of GitHub developers/Output/Adjacency List.csv");
	for (unsigned long long vertex = 0; vertex < /*(*this).vertices*/ 20; vertex++)
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
	for (unsigned long long row = 0; row < /*(*this).vertices*/ 300; row++)
	{
		for (unsigned long long column = 0; column < /*(*this).vertices*/ 300; column++)
		{
			file << (*this).adjacencyMatrix[row][column];
			if (column < /*(*this).vertices*/ 300 - 1)
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
	for (unsigned long long row = 0; row < /*(*this).vertices*/100; row++)
	{
		for (unsigned long long column = 0; column < /*(*this).vertices*/100; column++)
		{
			file << (*this).incidenceMatrix[row][column];
			if (column < /*(*this).vertices*/100 - 1)
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
	for (unsigned long long i = 0; i < vertices; i++) {
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
	if (BFS(source, destination, predecessor, distance)) {
		// Print the shortest distance and path
		std::cout << "Shortest distance between " << source << " and " << destination << " is " << distance[destination] << std::endl;

		std::vector<Type> path;
		Type currentVertex = destination;
		path.push_back(currentVertex);
		while (predecessor[currentVertex] != -1) {
			currentVertex = predecessor[currentVertex];
			path.push_back(currentVertex);
		}
		std::cout << "Shortest path is: ";
		for (typename std::vector<Type>::reverse_iterator it = path.rbegin(); it != path.rend(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
	}
	else {
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