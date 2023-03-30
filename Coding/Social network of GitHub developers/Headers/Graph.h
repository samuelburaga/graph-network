#pragma once
#include <list>

template <class Type> 
class Graph
{
private:
	unsigned long long vertices = 0;
	std::list<Type>* adjList;
public:
	Graph();
	Graph(unsigned long long);
	//Graph(const Graph <Type>&);
	void inputData();
};
template <class Type> Graph <Type>::Graph()
{
	(*this).vertices = 0;
}
template <class Type> Graph <Type>::Graph(unsigned long long vertices)
{
	(*this).vertices = vertices;
}