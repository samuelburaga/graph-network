#pragma once
#include <sstream>
#include <string>

template <typename Type> Type convert_to(const std::string& string)
{
    std::istringstream ss(string);
    Type number;
    ss >> number;
    return number;
}