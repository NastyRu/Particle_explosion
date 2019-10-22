#ifndef PARTICLES_H
#define PARTICLES_H

#include "points.h"

class Particle
{
public:
    Particle() {}
    Particle(Point_3d point, Point_3d v, double m);
    Particle(Point_3d point);
    ~Particle() {}

    void set_p(const Point_3d p);
    Point_3d get_p() const;

    void set_v(const Point_3d v);
    Point_3d get_v() const;

    void set_m(const double m);
    double get_m() const;

private:
    Point_3d point;

    Point_3d speed;

    double m;
};

#endif // PARTICLES_H
