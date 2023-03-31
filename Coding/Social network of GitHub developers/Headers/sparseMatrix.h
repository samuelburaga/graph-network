#include <iostream>
#include <vector>
#include <algorithm>

template <class Type> class sparseMatrix {
private:
    std::vector<Type> values;
    std::vector<unsigned long long> row_indices;
    std::vector<unsigned long long> col_indices;
    unsigned long long num_rows;
    unsigned long long num_cols;
public:
    sparseMatrix(unsigned long long nrows, unsigned long long ncols) : num_rows(nrows), num_cols(ncols) {}
    void add(unsigned long long row, unsigned long long col, Type value) {
        values.push_back(value);
        row_indices.push_back(row);
        col_indices.push_back(col);
    }
    Type get(unsigned long long row, unsigned long long col) const {
        for (unsigned long long i = 0; i < values.size(); i++) {
            if (row_indices[i] == row && col_indices[i] == col) {
                return values[i];
            }
        }
        return 0;
    }
    void print() const{
        for (unsigned long long row = 0; row < 10; row++) {
            for (unsigned long long col = 0; col < 10; col++) {
                std::cout << get(row, col) << " ";
            }
            std::cout << std::endl;
        }
    }
};