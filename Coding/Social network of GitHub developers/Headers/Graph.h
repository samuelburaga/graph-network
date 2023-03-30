#pragma once
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
public:
	Graph();
	Graph(const unsigned long long&);
	void inputData();
	void addEdge(const unsigned long long&, const unsigned long long&);
	unsigned long long& getVertices();
	template <class Type> friend std::ostream& operator<<(std::ostream&, Graph <Type>&);
	void printAdjacencyMatrix();
	void printAdjacencyList();
};
template <class Type> Graph <Type>::Graph()
{
	(*this).vertices = 0;
	(*this).adjacencyMatrix = new int* [0];
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