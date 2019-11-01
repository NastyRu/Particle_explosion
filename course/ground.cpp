#include "ground.h"

Ground::Ground(Point_3d p1, Point_3d p2, Point_3d p3, Point_3d p4) {
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    this->p4 = p4;
}

vector<Point_3d> Ground::get_points() {
    return vector<Point_3d>({p1, p2, p3, p4});
}
