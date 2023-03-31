#include <iostream>
#include "inputData.cpp"

int main()
{
	Graph <unsigned long long> GitHub(8000);
	GitHub.inputData();
	std::cout << GitHub;
	GitHub.printShortestDistance(119, 562);
	return 0;
}