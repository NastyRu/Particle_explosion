#include "positions.h"

Position::Position(Point_3d center) {
    this->center = center;
}

Position::Position(vector<Particle> particle) {
    Point_3d p = particle[0].get_p();
    double max_x = p.get_x(), min_x = p.get_x(), max_y = p.get_y(), min_y = p.get_y(), max_z = p.get_z(), min_z = p.get_z();
    for (int i = 0; i < particle.size(); i++) {
        Point_3d p = particle[i].get_p();
        if (p.get_x() > max_x) {
            max_x = p.get_x();
        }
        if (p.get_x() < min_x) {
            min_x = p.get_x();
        }
        if (p.get_y() > max_y) {
            max_y = p.get_y();
        }
        if (p.get_y() < min_y) {
            min_y = p.get_y();
        }
        if (p.get_z() > max_z) {
            max_z = p.get_z();
        }
        if (p.get_z() < min_z) {
            min_z = p.get_z();
        }
    }
    Point_3d tmp;
    tmp.set_x((min_x + max_x) / 2);
    tmp.set_y((min_y + max_y) / 2);
    tmp.set_z((min_z + max_z) / 2);
    center = tmp;
}

void Position::offset_center(int dx, int dy, int dz) {
    center.offset(dx, dy, dz);
}

Point_3d &Position::get_center() {
    return center;
}
