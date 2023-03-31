#pragma once
#include "sorted_array.h"
template<class T> class Entry
{
public:
	unsigned int lin;
	unsigned int col;
	T val;
	Entry() {}
	Entry(unsigned int l, unsigned int c, T const& v) :lin(l),
		col(c), val(v)
	{
		if (v == 0) {
			cout << "Eroare! Valoare nula la linia " << lin <<
				", coloana " << col << endl;
		}
	}
	Entry(Entry<T> const& t)
	{
		if (t.val == 0) {
			cout << "Eroare! Valoare nula la linia " << t.lin <<
				", coloana " << t.col << endl;
		}
		val = t.val;
		lin = t.lin;
		col = t.col;
	}
	void setVal(unsigned int l, unsigned int c, T const& v)
	{
		lin = l;
		col = c;
		val = v;
		if (v == 0) {
			cout << "Eroare! Valoare nula la linia " << lin <<
				", coloana " << col << endl;
		}
	}
	unsigned int isNull() const
	{
		return ((v == 0.0));
	}
	unsigned int operator<(Entry<T> const& t)
	{
		return ((lin < t.lin) || ((lin == t.lin) && (col < t.col)));
	}
	unsigned int operator<=(Entry<T> const& t)
	{
		return ((lin < t.lin) || ((lin == t.lin) && (col <= t.col)));
	}
	unsigned int operator>(Entry<T> const& t)
	{
		return ((lin > t.lin) || ((lin == t.lin) && (col > t.col)));
	}
	unsigned int operator>=(Entry<T> const& t)
	{
		return ((lin > t.lin) || ((lin == t.lin) && (col >= t.col)));
	}
	unsigned int operator==(Entry<T> const& t)
	{
		return ((lin == t.lin) && (col == t.col));
	}
	unsigned int eq(Entry<T> const& t)
	{
		return ((lin == t.lin) && (col == t.col) && (val == t.val));
	}
	Entry<T>& operator=(Entry<T> const& t)
	{
		if (t.val == 0) {
			cout << "Eroare! Valoare nula la linia " << t.lin <<
				", coloana " << t.col << endl;
		}
		val = t.val;
		lin = t.lin;
		col = t.col;
		return *this;
	}
};
template<class T> class sparseMatrix
{
protected:
	unsigned int nrLin;
	unsigned int nrCol;
	unsigned int nrVal;
	sorted_array<Entry<T> > data; 
	sparseMatrix(unsigned int l, unsigned int c) :nrLin(l), nrCol(c), nrVal(0) {}
	~sparseMatrix() : nrLin(0), nrCol(0), nrVal(0) {};
	unsigned int isNull()
	{
		return (nrVal == 0);
	}
	sorted_array <Entry<T> >& getData()
	{
		return data;
	}
	sparseMatrix<T>& addEntry(Entry<T> const& t)
	{
		if ((t.lin <= 0) || (t.lin > nrLin) || (t.col <= 0) || (t.col > nrCol))
		{
			cout << "Eroare! dimensiuni incorecte !" << endl;
			return *this;
		}
		int pos = data.findValue(t);
		if (pos < 0)
		{
			data = data + t;
			nrVal++;
		}
		else
		{
			Entry<T>& curent = data[pos];
			T sum = curent.val + t.val;
			if (sum == 0.0)
			{
				data = data - curent;
				nrVal--;
			}
			else
			{
				curent.val = sum;
			}
		}
		return (*this);
	}
	sparseMatrix<T>& subEntry(Entry<T>& t)
	{
		t.coef = -t.coef;
		return addEntry(t);
	}
	sparseMatrix<T>& addValue(unsigned int l, unsigned int c, T const& t1)
	{
		Entry<T> t(l, c, t1);
		return addEntry(t);
	}
	sparseMatrix<T>& subValue(unsigned int l, unsigned int c, const& t1)
	{
		Entry<T> t(l, c, -t1);
		return addValue(t1);
	}
	sparseMatrix& reset()
	{
		data.setLength(0);
		nrVal = 0;
	}
	sparseMatrix<T>& operator=(sparseMatrix<T> const& p)
	{
		data = p.data;
		nrLin = p.nrLin;
		nrCol = p.nrCol;
		nrVal = p.nrVal;
		return *this;
	}
	sparseMatrix<T>& operator+(Entry<T> const& t)
	{
		return addEntry(t);
	}
	sparseMatrix<T>& operator+(sparseMatrix<T> const& p);
	sparseMatrix<T>& operator-(Entry<T> const& t);
	{
		return subEntry(t);
	};
	sparseMatrix<T>& operator-(sparseMatrix<T> const& p);
	sparseMatrix<T>& operator*(T const& t);
	template <class T> friend ostream& operator<<(ostream& o, sparseMatrix<T>& p);
};

template<class T> sparseMatrix<T>& sparseMatrix<T>::operator+(sparseMatrix<T> const& p)
{
	if ((p.lin != lin) || (p.col != col))
	{
		cout << "Eroare! nu pot aduna matrici de dimensiuni diferite!"<<endl;
			return *this;
	}
	for (unsigned int i = 0; i < p.data.getLength(); i++)
		addEntry(p.data[i]);
	return *this;
}

template<class T> sparseMatrix<T>& sparseMatrix<T>::operator-(sparseMatrix<T> const& p)
{
	if ((p.lin != lin) || (p.col != col))
	{
		cout << "Eroare! nu pot aduna matrici de imensiuni diferite!" << endl;
		return *this;
	}
	for (unsigned int i = 0; i < p.data.getLength(); i++)
		subEntry(p.data[i]);
	return *this;
}

template<class T> sparseMatrix<T>& sparseMatrix<T>::operator*(T const& t)
{
	if (t == 0)
	{
		data.setLength(0);
		nrVal = 0;
	}
	else
		for (unsigned int i = 0; i < data.getLength(); i++)
			data[i].val = data[i].val * t;

	return *this;
}

template<class T> ostream & operator<<(ostream & o, sparseMatrix<T>&p)
{
	unsigned int k = 0;
	for (unsigned int i = 0; i < p.nrLin; i++)
	{
		for (unsigned int j = 0; j < p.nrCol; j++)
			if ((k < p.data.getLength()) && (p.data[k].lin == i)

				&& (p.data[k].col == j))

			{
				cout << p.data[k++].val << "\t";
			}
			else
			{
				cout << 0 << "\t";
			}
		cout << endl;
	}
	return o;
}