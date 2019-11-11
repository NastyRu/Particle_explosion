#ifndef DRAW_H
#define DRAW_H

#include "base_draw.h"
#include <QPainter>
#include "points.h"
#include "camera.h"
#include "buffer.h"
#include <cmath>
#include <QPolygon>
#include <thread>

static mutex data_lock;

class DrawQt : public Base_draw
{
public:
    DrawQt(QPainter &pa, Camera &cam) : p(pa), camera(cam) {}
    ~DrawQt() override {}

    void drawline(Point_3d begin, Point_3d end) override;
    void drawpoint(Point_3d point) override;
    void drawcircle(Point_3d point, int r) override;
    void drawcircles(vector<Point_3d> point, vector<int> r) override;
    void drawpolygon(Point_3d p1, Point_3d p2, Point_3d p3, Point_3d p4) override;

private:
    QPainter &p;
    Camera &camera;
    Zbuffer buf;
};

#endif // DRAW_H
