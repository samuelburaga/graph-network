#pragma once
#include <iostream>
#include <string>

using namespace std;

template <class Type> class Array
{
protected:
	unsigned long long base, length;
	Type* data;
public:
	string name;
	Array();
	Array(unsigned long long);
	Array(string);
	Array(unsigned long long, unsigned long long, string);
	Array(const Array <Type>&);
	unsigned long long get_base();
	unsigned long long get_length();
	void set_base(unsigned long long);
	void set_length(unsigned long long);
	Array <Type>& operator=(const Array <Type>&);
	Type& operator[](unsigned long long index); //l value
	const Type& operator[](unsigned long long) const; //r value
	Array <Type>& operator+(const Array <Type>&);
	template <class Type> friend istream& operator>>(istream&, Array <Type>&);
	template <class Type> friend ostream& operator<<(ostream&, const Array <Type>&);
	bool is_empty();
	void print();
	void visit(void(*f)(Type&));
	~Array();
};
template <class Type> Array <Type>::Array()
{
	(*this).base = -1;
	(*this).length = 0;
	(*this).data = new Type[0];
}
template <class Type> Array <Type>::Array(unsigned long long base)
{
	(*this).base = base;
	(*this).length = 0;
	(*this).data = new Type[0];
}
template <class Type> Array <Type>::Array(string array_name) :name(array_name)
{
	(*this).base = -1;
	(*this).length = 0;
	(*this).data = new Type[0];
}
template <class Type> Array <Type>::Array(unsigned long long base, unsigned long long length, string name)
{
	(*this).base = base;
	(*this).length = length;
	(*this).name = name;
	(*this).data = new Type[base + length];
}
template <class Type> Array <Type>::Array(const Array <Type>& second_array)
{
	if (this != &second_array)
	{
		(*this).base = second_array.base;
		(*this).length = second_array.length;
		(*this).data = new Type[base + length];
		for (long long index = (long long)(base); index <= (long long)(base + length - 1); index++)
		{
			(*this)[index] = second_array[index];
		}
		(*this).name = second_array.name;
	}
}
template <class Type> unsigned long long Array <Type>::get_base()
{
	return (*this).base;
}
template <class Type> unsigned long long Array <Type>::get_length()
{
	return (*this).length;
}
template <class Type> void Array <Type>::set_base(unsigned long long new_base)
{
	(*this).base = new_base;
}
template <class Type> void Array <Type>::set_length(unsigned long long new_length)
{
	(*this).length = new_length;
}
template <class Type> Array <Type>& Array <Type>::operator=(const Array <Type>& second_array)
{
	if (this != &second_array)
	{
		delete[](*this).data;
		(*this).base = second_array.base;
		(*this).length = second_array.length;
		(*this).data = new Type[base + length];
		for (unsigned long long index = base; index <= base + length - 1; index++)
		{
			(*this)[index] = second_array[index];
		}
		return (*this);
	}
}
template <class Type> Type& Array <Type>::operator[](unsigned long long index)
{
	try
	{
		if (index < (*this).base || index >(*this).base + (*this).length - 1)
			throw new exception("The index is out of scope!");
		return (*this).data[index];
	}
	catch (...)
	{
		cout << "The index is out of scope!";
	}
}
template <class Type> const Type& Array <Type>::operator[](unsigned long long index) const
{
	try
	{
		if (index < (*this).base || index >(*this).base + (*this).length - 1)
			throw new exception("The index is out of scope!");
		return (*this).data[index];
	}
	catch (...)
	{
		cout << "The index is out of scope!";
	}
}
template <class Type> Array <Type>& Array <Type>::operator+(const Array <Type>& second_array)
{
	Array <Type> sum((*this).name + " + " + second_array.name);
	return sum;
}
template <class Type> istream& operator>>(istream& input, Array <Type>& array)
{
	input >> array.base >> array.length >> array.name;
	array.data = new Type[array.base + array.length];
	for (unsigned long long index = array.base; index <= array.base + array.length - 1; index++)
	{
		input >> array[index];
	}
	return input;
}
template <class Type> ostream& operator<<(ostream& output, const Array <Type>& array)
{
	try
	{
		if (array.length == 0)
			throw new exception("The array is empty!\n");
		output << array.name << " = ";
		for (unsigned long long index = array.base; index <= array.base + array.length - 1; index++)
		{
			output << array[index] << " ";
		}
		output << "\n";
		return output;
	}
	catch (...)
	{
		cout << "The " << array.name << " is empty!\n";
	}
}
template <class Type> bool Array <Type>::is_empty()
{
	return (*this).length == 0;
}
template <class Type> void Array <Type>::print()
{
	cout << (*this);
}
template <class Type> void Array <Type>::visit(void((*f)(Type&)))
{
	for (unsigned long long index = (*this).base; index <= (*this).base + (*this).length - 1; index++)
	{
		f((*this).data[index]);
	}
}
template <class Type> Array <Type>::~Array()
{
	(*this).base = -1;
	(*this).length = 0;
	if ((*this).data != NULL)
	{
		delete[](*this).data;
	}
}