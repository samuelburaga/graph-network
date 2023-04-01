#include <iostream>
#include "inputData.cpp"
#include "Graph.h"

template <class Type> void Graph <Type>::runGraph()
{
    (*this).inputData();
    (*this).printAdjacencyList();
    (*this).printShortestDistance(2, 870);
    (*this).countAndPrintConnectedComponents();
    (*this).printEulerianCycles();
    (*this).printMST();
}
