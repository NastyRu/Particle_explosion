#ifndef POSITIONS_H
#define POSITIONS_H

#include "particles.h"
#include "iterators.h"
#include <QDebug>

class Position
{
public:
    Position() {}
    Position(Point_3d center);
    Position(vector<Particle> particle);
    ~Position() {}

    void offset_center(int dx, int dy, int dz);
    Point_3d &get_center();

private:
    Point_3d center;
};

#endif // POSITIONS_H
