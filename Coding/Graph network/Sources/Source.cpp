#include <iostream>
#include "inputData.cpp"

int main()
{
	Graph <unsigned long long> G(4941, 6954);
	std::cout << "The graph is processed...\n";
	G.inputData();	
	G.countAndPrintConnectedComponents();
	G.printShortestDistance(2, 870);
	G.printMST();
	G.printEulerianCycles();
	G.printMaxMatching();
	std::cout << G;
	return 0;
}