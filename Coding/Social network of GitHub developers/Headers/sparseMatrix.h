#include <iostream>
#include <vector>
#include <algorithm>

template <class Type> class sparseMatrix {
private:
    std::vector<Type> values;
    std::vector<unsigned long long> row_indices;
    std::vector<unsigned long long> column_indices;
    unsigned long long numberOfRows;
    unsigned long long numberOfColumns;
public:
    sparseMatrix() {};
    sparseMatrix(unsigned long long numberOfRows, unsigned long long numberOfColumns) : numberOfRows(numberOfRows), numberOfColumns(numberOfColumns) {}
    void add(unsigned long long row, unsigned long long column, Type value) {
        values.push_back(value);
        row_indices.push_back(row);
        column_indices.push_back(column);
    }
    Type get(unsigned long long row, unsigned long long column) const {
        for (unsigned long long index = 0; index < values.size(); index++) {
            if (row_indices[index] == row && column_indices[index] == column) {
                return values[index];
            }
        }
        return 0;
    }
    void print() const{
        for (unsigned long long row = 0; row < 10; row++) {
            for (unsigned long long column = 0; column < 10; column++) {
                std::cout << get(row, column) << " ";
            }
            std::cout << std::endl;
        }
    }
    unsigned long long& getNumberOfRows()
    {
        return (*this).numberOfRows;
    }
    unsigned long long& getNumberOfColumns()
    {
        return (*this).numberOfColumns;
    }
};