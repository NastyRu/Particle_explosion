#include "matrix.h"

vector<double> Matrix::operator *(const vector<double> &vec) {
    vector<double> tmp(4, 0);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
             tmp[i] += vec[j] * matrix[i][j];
        }
    }
    return tmp;
}
