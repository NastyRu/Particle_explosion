#ifndef BASE_DRAW_H
#define BASE_DRAW_H

#include <points.h>

class Base_draw
{
public:
    Base_draw() {}
    virtual ~Base_draw() {}

    virtual void drawline(Point_3d begin, Point_3d end) = 0;
    virtual void drawpoint(Point_3d point) = 0;
    virtual void drawpolygon(Point_3d p1, Point_3d p2, Point_3d p3, Point_3d p4)  = 0;
};

#endif // BASE_DRAW_H
