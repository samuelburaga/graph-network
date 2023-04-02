#include <iostream>
#include "inputData.cpp"

int main()
{
	Graph <unsigned long long> G(4941, 6954);
	std::cout << "The graph is processed...\n";
	G.inputData();	
	G.printShortestDistance(2, 870);
	G.countAndPrintConnectedComponents();
	G.printEulerianCycles();
	G.printMST();
	G.printMaxMatching();
	std::cout << G;
	return 0;
}