#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include "points.h"

using namespace std;

class Matrix
{
public:
    Matrix() {
        matrix = vector<vector<double>>(4, vector<double>(4, 0));
    }
    Matrix(Point_3d point) {
        matrix = vector<vector<double>>(4, vector<double>(4, 0));
        matrix[0][0] = 1;
        matrix[0][3] = -point.get_x();
        matrix[1][1] = 1;
        matrix[1][3] = -point.get_y();
        matrix[2][3] = -1 / point.get_z();
        matrix[3][3] = 1;
    }
    ~Matrix() {}

    vector<double> operator *(const vector<double> &vec);

private:
    vector<vector<double>> matrix;
    int n = 0;
};

#endif // MATRIX_H
