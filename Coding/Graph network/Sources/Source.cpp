#include <iostream>
#include "inputData.cpp"

int main()
{
	Graph <unsigned long long> GitHub(4941, 6954);
	GitHub.inputData();	
	//std::cout << GitHub;
	//GitHub.printShortestDistance(2, 870);
	//GitHub.countAndPrintConnectedComponents();
	//GitHub.printEulerianCycles();
	//GitHub.printHamiltonianCycle(1, 2);
	//GitHub.printMST();
	GitHub.printMaxMatching();
	Graph<int> g(4);
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 2);
	g.addEdge(2, 3);
	g.printMaxMatching();

	return 0;
}