#include "particles.h"

Particle::Particle(Point_3d point, Point_3d v, double m, int r) {
    this->point = point;
    this->speed = v;
    this->m = m;
    this->radius = r;
}

Particle::Particle(Point_3d point, int r) {
    this->point = point;
    this->speed = Point_3d(0,0,0);
    this->m = 1;
    this->radius = r;
}

Particle::Particle(Point_3d point) {
    this->point = point;
    this->speed = Point_3d(0,0,0);
    this->m = 1;
    this->radius = 1;
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

void Particle::set_r(const int r) {
    this->radius = r;
}

int Particle::get_r() const {
    return radius;
}
