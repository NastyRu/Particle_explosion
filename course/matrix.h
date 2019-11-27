#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include "points.h"

using namespace std;

class Matrix
{
public:
    Matrix() {}
    Matrix(int row, int col) {
        matrix = vector<vector<double>>(row, vector<double>(col, 0));
    }
    Matrix(int row, int col, int value) {
        matrix = vector<vector<double>>(row, vector<double>(col, value));
    }
    ~Matrix() {}

    vector<double> operator *(const vector<double> &vec);
    Matrix operator *(Matrix &vec);
    int size() {
        return matrix.size();
    }

    class Row {
        friend class Matrix;
        public:
            double& operator[](int col) {
                return parent.matrix[row][col];
            }
            int size() {
                return parent.matrix[row].size();
            }
        private:
            Row(Matrix &parent_, int row_) :
                parent(parent_), row(row_) {
            }

            Matrix& parent;
            int row;
        };

    Row operator [](int row) {
        return Row(*this, row);
    }

private:
    vector<vector<double>> matrix;
    int n = 0;
};

#endif // MATRIX_H
