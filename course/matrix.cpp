#include "matrix.h"

vector<double> Matrix::operator *(const vector<double> &vec) {
    vector<double> tmp(matrix.size(), 0);
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
             tmp[i] += vec[j] * matrix[i][j];
        }
    }
    return tmp;
}

Matrix Matrix::operator *(Matrix &vec) {
    Matrix tmp = Matrix(matrix.size(), vec[0].size());
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < vec[0].size(); j++) {
            for (int k = 0; k < matrix[0].size(); k++) {
                tmp[i][j] += vec[k][j] * matrix[i][k];
            }
        }
    }
    return tmp;
}
