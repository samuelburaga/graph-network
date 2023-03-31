#pragma once
#include "Array.h"
#include <iostream>
#include <string>
using namespace std;

template <class Type>
class sorted_array :public Array <Type>
{
public:
	sorted_array();
	sorted_array(unsigned long long);
	sorted_array(string);
	//sorted_array(const sorted_array <Type>&);
	long long search_value(const Type&);
	sorted_array <Type>& add_value(const Type&);
	sorted_array <Type>& operator+(const Type& value);
	sorted_array <Type>& remove_value(const Type&);
	sorted_array <Type>& operator-(const Type& value);
	sorted_array <Type>& merge(const sorted_array <Type>& second_sorted_array);
	sorted_array <Type>& operator*(const Type& value);
	sorted_array <Type>& operator/(const Type& value);
	//sorted_array& operator+(SortArray const& sa);
	//sorted_array& operator-(T const& val);
	//sorted_array& operator+(const sorted_array <Type>& second_sorted_array);
	//sorted_array& operator-(const sorted_array <Type>& second_sorted_array);
	sorted_array <Type>& operator=(const sorted_array <Type>&);
	sorted_array <Type>& operator=(Array <Type>&);
	template <class Type> friend istream& operator>>(istream&, sorted_array <Type>&);
	~sorted_array();
};
template <class Type> sorted_array <Type>::sorted_array() : Array <Type>()
{
}
template <class Type> sorted_array <Type>::sorted_array(unsigned long long base) : Array <Type>(base)
{
}
template <class Type> sorted_array <Type>::sorted_array(string name) : Array <Type>(name)
{
}
//template <class Type> sorted_array <Type>::sorted_array(const sorted_array <Type>& second_sorted_array)
//{
//	if (this != &second_sorted_array)
//	{
//		(*this).base = second_sorted_array.base;
//		(*this).length = second_sorted_array.length;
//		(*this).data = new Type[(*this).base + (*this).length];
//		for (unsigned long long index = (*this).base; index <= (*this).base + (*this).length - 1; index++)
//		{
//			(*this)[index] = second_sorted_array[index];
//		}
//		(*this).name = second_sorted_array.name;
//	}
//}
template <class Type> long long sorted_array <Type>::search_value(const Type& value)
{
	long long left = (*this).base, middle, right = (*this).base + (*this).length - 1;
	while (left <= right)
	{
		middle = (left + right) / 2;
		if ((*this)[middle] == value)
		{
			return middle;
		}
		else
			if ((*this)[middle] < value)
			{
				left = middle + 1;
			}
			else
			{
				right = middle - 1;
			}
	}
	return (*this).base - 1;
}
template <class Type> sorted_array <Type>& sorted_array <Type>::add_value(const Type& value)
{
	Type* new_data = new Type[(*this).base + (*this).length + 1];
	long long index = (*this).base;
	while (index <= (long long)((*this).base + (*this).length - 1) && (*this)[index] < value)
	{
		new_data[index] = (*this)[index];
		index++;
	}
	new_data[index] = value;
	while (index <= (long long)((*this).base + (*this).length - 1))
	{
		new_data[index + 1] = (*this)[index];
		index++;
	}
	(*this).length++;
	delete[](*this).data;
	(*this).data = new_data;
	return (*this);
}
template <class Type> sorted_array <Type>& sorted_array <Type>::operator+(const Type& value)
{
	return (*this).add_value(value);
}
template <class Type> sorted_array <Type>& sorted_array <Type>::remove_value(const Type& value)
{
	long long position = (*this).search_value(value);
	if (position >= (*this).base)
	{
		Type* new_data = new Type[(*this).base + (*this).length - 1];
		unsigned long long index = (*this).base;
		while (index != position)
		{
			new_data[index] = (*this)[index];
			index++;
		}
		index++;
		while (index <= (*this).base + (*this).length - 1)
		{
			new_data[index - 1] = (*this)[index];
			index++;
		}
		(*this).length--;
		delete[](*this).data;
		(*this).data = new_data;
		return (*this);
	}
	return (*this);

}
template <class Type> sorted_array <Type>& sorted_array <Type>::operator-(const Type& value)
{
	return (*this).remove_value(value);
}
template <class Type> sorted_array <Type>& sorted_array <Type>::merge(const sorted_array <Type>& second_sorted_array)
{
	if (this != &second_sorted_array)
	{

	}
}
template <class Type> sorted_array <Type>& sorted_array <Type>::operator=(Array <Type>& array)
{
	if (this != &array)
	{
		(*this).base = array.get_base();
		(*this).length = array.get_length();
		(*this).data = new Type[(*this).base + (*this).length];
		for (unsigned long long index = (*this).base; index <= (*this).base + (*this).length - 1; index++)
		{
			(*this)[index] = array[index];
		}
		(*this).name = array.name;
	}
	return (*this);
}
template <class Type> sorted_array <Type>& sorted_array <Type>::operator=(const sorted_array <Type>& second_sorted_array)
{
	if (this != &second_sorted_array)
	{
		(*this).base = second_sorted_array.base;
		(*this).length = second_sorted_array.length;
		(*this).data = new Type[(*this).base + (*this).length];
		for (long long index = (*this).base; index <= (long long)((*this).base + (*this).length - 1); index++)
		{
			(*this)[index] = second_sorted_array[index];
		}
		(*this).name = second_sorted_array.name;
	}
	return (*this);
}
template <class Type> sorted_array <Type>& sorted_array <Type>::operator*(const Type& value)
{
	for (unsigned long long index = (*this).base; index <= (*this).base + (*this).length - 1; index++)
	{
		(*this)[index] = (*this)[index] * value;
	}
	return (*this);
}
template <class Type> sorted_array <Type>& sorted_array <Type>::operator/(const Type& value)
{
	return (*this) * (1 / value);
}
template <class Type> istream& operator>>(istream& input, sorted_array <Type>& sorted_array)
{
	input >> sorted_array.base >> sorted_array.name;
	return input;
}
template <class Type> sorted_array <Type>::~sorted_array()
{

}