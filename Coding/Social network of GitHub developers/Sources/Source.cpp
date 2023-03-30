#include <iostream>
#include "inputData.cpp"

int main()
{
	Graph <unsigned long long> GitHub(37700);
	GitHub.inputData();
	std::cout << GitHub;
	return 0;
}