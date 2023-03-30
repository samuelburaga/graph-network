#include "../Headers/Graph.h"
#include "../Headers/stringToType.h"
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
		std::string titles;
		getline(file, titles);
		std::string line;
		unsigned long long edge = 0;
		while (getline(file, line) && edge <= 100)
		{
			std::istringstream ss(line);
			std::string firstColumn, secondColumn;
			getline(ss, firstColumn, ',');
			getline(ss, secondColumn, ',');
			int num1 = stoi(firstColumn);
			int num2 = stoi(secondColumn);
			Type u = convert_to <Type>(firstColumn);
			Type v = convert_to <Type>(secondColumn);
		/*	if (u > (*this).vertices)
			{
				(*this).vertices = u;
			}
			if (v > (*this).vertices)
			{
				(*this).vertices = v;
			}
			(*this).vertices++;*/
			edge++;
			(*this).addEdge(u, v, edge);
		}
	}
	catch (...)
	{
		throw new std::exception("File error!");
	}
}