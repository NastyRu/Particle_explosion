#ifndef GROUND_H
#define GROUND_H

#include "objects.h"
#include "base_draw.h"
#include "particles.h"

using namespace std;

class Ground : public Visible_object
{
public:
    Ground() {}
    ~Ground() {}

    Ground(Point_3d p1, Point_3d p2, Point_3d p3, Point_3d p4);
    char type() override { return 'g'; }

    vector<Point_3d> get_points();
private:
    Point_3d p1;
    Point_3d p2;
    Point_3d p3;
    Point_3d p4;
};


#endif // GROUND_H
