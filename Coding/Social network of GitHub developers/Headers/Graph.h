#pragma once
#include <list>

template <class Type> 
class Graph
{
private:
	unsigned long long vertices;
	std::list<Type>* adjacencyList;
	bool** adjacencyMatrix;
public:
	Graph();
	Graph(unsigned long long);
	Graph(const Graph <Type>&);
	void inputData();
	void addEdge(const Type&, const Type&);
	unsigned long long& getVertices();
};
template <class Type> Graph <Type>::Graph()
{
	(*this).vertices = 0;
}
template <class Type> Graph <Type>::Graph(unsigned long long vertices)
{
	(*this).vertices = vertices;
}
template <class Type> void Graph <Type>::addEdge(const Type& u, const Type& v)
{

}
template <class Type> unsigned long long& Graph <Type>::getVertices()
{
	return (*this).vertices;
}