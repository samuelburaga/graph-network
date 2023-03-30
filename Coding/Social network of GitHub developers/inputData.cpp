#include "Headers/Graph.h"
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

template <class Type> 
void Graph <Type>::inputData()
{
	try 
	{
        std::ifstream file;
		file.open("D:/ULBS/Anul II/Semestrul II/Modulul 1/Algoritmica grafurilor/Project/Coding/Social network of GitHub developers/Resources/git_web_ml/musae_git_edges.csv");
		std::string line;
		getline(file, line);
		//std::string line;
		int x = 0;
		while (getline(file, line))
		{
			std::istringstream ss(line);
			std::string col1, col2;
			getline(ss, col1, ',');
			getline(ss, col2, ',');
			int num1 = stoi(col1);
			int num2 = stoi(col2);

			// Do something with the data, e.g. print it
			std::cout << "Number 1: " << num1 << ", Number 2: " << num2 << std::endl;
		}

	}
	catch (...)
	{
		throw new std::exception("File error!");
	}
}