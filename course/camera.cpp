#include "camera.h"

void Camera::set_position(const Point_3d &point) {
    this->position = point;
}

Point_3d Camera::get_position() {
    return position;
}

Matrix Camera::get_matrix(){
    return matrix;
}

void Camera::scale(double k) {
    Matrix matrixK = Matrix(3,3);
    matrixK[0][0] = k;
    matrixK[1][1] = k;
    matrixK[2][2] = k;

    Matrix cam = Matrix(3,3);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cam[i][j] = matrix[i][j];
        }
    }

    cam = cam * matrixK;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrix[i][j] = cam[i][j];
        }
    }
}

void Camera::rotation(double angleX, double angleY) {
    Matrix matrixX = Matrix(3,3);
    Matrix matrixY = Matrix(3,3);
    Matrix cam = Matrix(3,3);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cam[i][j] = matrix[i][j];
        }
    }

    matrixX[0][0] = 1;
    matrixX[1][1] = cos(angleX);
    matrixX[1][2] = -sin(angleX);
    matrixX[2][1] = sin(angleX);
    matrixX[2][2] = cos(angleX);

    matrixY[0][0] = cos(angleY);
    matrixY[0][2] = sin(angleY);
    matrixY[1][1] = 1;
    matrixY[2][0] = -sin(angleY);
    matrixY[2][2] = cos(angleY);

    cam = cam * matrixX;
    cam = cam * matrixY;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrix[i][j] = cam[i][j];
        }
    }
}
