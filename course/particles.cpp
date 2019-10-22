#include "particles.h"

Particle::Particle(Point_3d point, Point_3d v, double m) {
    this->point = point;
    this->speed = speed;
    this->m = m;
}

Particle::Particle(Point_3d point) {
    this->point = point;
    this->speed = Point_3d(0,0,0);
    this->m = 1;
}

void Particle::set_p(const Point_3d p) {
    this->point = p;
}

Point_3d Particle::get_p() const {
    return point;
}

void Particle::set_v(const Point_3d v) {
    this->speed = v;
}

Point_3d Particle::get_v() const {
    return speed;
}

void Particle::set_m(const double m) {
    this->m = m;
}

double Particle::get_m() const {
    return m;
}
