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
