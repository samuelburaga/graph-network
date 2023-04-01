#include "Graph.h"
#include "stringToType.h"
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

template <class Type> void Graph <Type>::inputData()
{
    try
    {
        std::ifstream file;
        file.open("D:/ULBS/Anul II/Semestrul II/Modulul 1/Algoritmica grafurilor/Project/App/GraphNetwork/Resources/CSV/lasftm_asia/lastfm_asia_edges.csv");
        std::string titles;
        getline(file, titles);
        std::string line;
        unsigned long long edge = 0;
        while (getline(file, line))
        {
            std::istringstream ss(line);
            std::string firstColumn, secondColumn;
            getline(ss, firstColumn, ',');
            getline(ss, secondColumn, ',');
            Type u = convert_to <Type>(firstColumn);
            Type v = convert_to <Type>(secondColumn);
            edge++;
            (*this).addEdge(u, v, edge);
        }
    }
    catch (...)
    {
        throw std::runtime_error("File error!");
    }
}
