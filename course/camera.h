#ifndef CAMERA_H
#define CAMERA_H

#include "objects.h"
#include "matrix.h"
#include "particles.h"

class Camera : public Unvisible_object
{
public:
    Camera(Point_3d pos) {
        position = pos;
        matrix = Matrix(4, 4);
        matrix[0][0] = 1;
        matrix[0][3] = pos.get_x();
        matrix[1][1] = 1;
        matrix[1][3] = pos.get_y();
        matrix[2][2] = 1;
        matrix[2][3] = -1 / pos.get_z();
        matrix[3][3] = 1;
        is_current = 1;
    }
    ~Camera() {}
    void set_position(const Point_3d &point);
    Point_3d get_position();
    Matrix get_matrix();

    void scale(double k);
    void rotation(double angleX, double angleY);

    bool is_current;
private:
    Matrix matrix;
    Point_3d position;
};

#endif // CAMERA_H
