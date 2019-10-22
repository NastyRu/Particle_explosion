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
        matrix = Matrix(position);
    }
    ~Camera() {}
    void set_position(const Point_3d &point);
    Point_3d get_position();
    Matrix get_matrix();

private:
    Matrix matrix;
    Point_3d position;
    Point_3d rotation;
    Point_3d scale;
    Point_3d offset;
};

#endif // CAMERA_H
