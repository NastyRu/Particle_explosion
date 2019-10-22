#ifndef DRAW_H
#define DRAW_H

#include "base_draw.h"
#include <QPainter>
#include "points.h"
#include "camera.h"

class DrawQt : public Base_draw
{
public:
    DrawQt(QPainter &pa, Camera & cam) : p(pa), camera(cam) {}
    ~DrawQt() {}

    void drawline(Point_3d begin, Point_3d end) override;
    void drawpoint(Point_3d point) override;

private:
    QPainter &p;
    Camera &camera;
};

#endif // DRAW_H
