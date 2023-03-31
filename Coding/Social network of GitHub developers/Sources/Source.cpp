#include <iostream>
#include "inputData.cpp"

int main()
{
	Graph <unsigned long long> GitHub(7624, 27.806);
	GitHub.inputData();	
	std::cout << GitHub;
	GitHub.printShortestDistance(2, 870);
	GitHub.countAndPrintConnectedComponents();
	//GitHub.findMST();
	return 0;
}