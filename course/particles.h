#ifndef PARTICLES_H
#define PARTICLES_H

#include "points.h"

class Particle
{
public:
    Particle() {}
    Particle(Point_3d point, int r, int m);
    Particle(Point_3d point, int r);
    Particle(Point_3d point);
    ~Particle() {}

    void set_p(const Point_3d p);
    Point_3d get_p() const;

    void set_v(const Point_3d v);
    Point_3d get_v() const;

    void set_m(const double m);
    double get_m() const;

    void set_r(const int r);
    int get_r() const;

    void collision(Particle &p);
    void update(int time);

private:
    Point_3d point;
    Point_3d speed;
    int m;
    int radius;
};

#endif // PARTICLES_H
