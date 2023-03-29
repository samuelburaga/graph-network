#pragma once
#include <list>
class Graph
{
private:
	unsigned long long vertices = 0;
	list<unsigned long long>* adjList;
public:
	Graph(unsigned long long);
	Graph(const Graph&);
};