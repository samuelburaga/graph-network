#pragma once
#include <list>
#include <iostream>

template <class Type> 
class Graph
{
private:
	unsigned long long vertices;
	std::list<Type>* adjacencyList;
	int** adjacencyMatrix;
public:
	Graph();
	Graph(const unsigned long long&);
	void inputData();
	void addEdge(const unsigned long long&, const unsigned long long&);
	unsigned long long& getVertices();
	template <class Type> friend std::ostream& operator<<(std::ostream&, Graph <Type>&);
};
template <class Type> Graph <Type>::Graph()
{
	(*this).vertices = 0;
	(*this).adjacencyMatrix = new int* [0];
}
template <class Type> Graph <Type>::Graph(const unsigned long long& vertices)
{
	(*this).vertices = vertices;
	(*this).adjacencyMatrix = new int* [(*this).vertices];
	for (unsigned long long index = 0; index < (*this).vertices; index++)
	{
		adjacencyMatrix[index] = new int[(*this).vertices];
	}
	for (unsigned long long row = 0; row < (*this).vertices; row++)
	{
		for (unsigned long long column = 0; column < (*this).vertices; column++)
		{
			(*this).adjacencyMatrix[row][column] = 0;
		}
	}
	std::cout << "DA";
}
template <class Type> unsigned long long& Graph <Type>::getVertices()
{
	return (*this).vertices;
}
template <class Type> void Graph <Type>::addEdge(const unsigned long long& u, const unsigned long long &v)
{
	std::cout << "DA'n";
	adjacencyMatrix[u][v] = 1;
	adjacencyMatrix[v][u] = 1;
}
template <class Type> std::ostream& operator<<(std::ostream& output, Graph <Type>& graph)
{
	for (unsigned long long row = 0; row < graph.vertices; row++)
	{
		for (unsigned long long column = 0; column < graph.vertices; column++)
		{
			output << graph.adjacencyMatrix[row][column] << " ";
		}
		output << "\n";
	}
	return output;
}