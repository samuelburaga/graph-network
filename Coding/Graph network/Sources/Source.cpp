#include <iostream>
#include "inputData.cpp"

int main()
{
	Graph <unsigned long long> GitHub(4942, 6954);
	GitHub.inputData();	
	//std::cout << GitHub;
	GitHub.printShortestDistance(2, 870);
	GitHub.countAndPrintConnectedComponents();
	GitHub.printEulerianCycles();
	GitHub.printMST();
	return 0;
}