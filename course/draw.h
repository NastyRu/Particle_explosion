#ifndef DRAW_H
#define DRAW_H

#include "base_draw.h"
#include <QPainter>
#include "points.h"
#include "camera.h"
#include <QPolygon>

class DrawQt : public Base_draw
{
public:
    DrawQt(QPainter &pa, Camera &cam) : p(pa), camera(cam) {}
    ~DrawQt() override {}

    void drawline(Point_3d begin, Point_3d end) override;
    void drawpoint(Point_3d point) override;
    void drawpolygon(Point_3d p1, Point_3d p2, Point_3d p3, Point_3d p4) override;

private:
    QPainter &p;
    Camera &camera;
};

#endif // DRAW_H
