#ifndef DRAW_H
#define DRAW_H

#include <QPainter>
#include "points.h"
#include "camera.h"
#include "raytracing.h"
#include <cmath>
#include <QPolygon>
#include <thread>
#include <QDebug>

static mutex data_lock;

class DrawQt
{
public:
    DrawQt(QPainter &pa, Camera &cam) : p(pa), camera(cam) {}
    ~DrawQt() {}

    void drawline(Point_3d begin, Point_3d end);
    void drawpoint(Point_3d point);
    void drawcircle(Point_3d point, int r);
    void drawmodel(vector<Point_3d> point, vector<int> r, vector<Point_3d> ground);
    void drawpolygon(Point_3d p1, Point_3d p2, Point_3d p3, Point_3d p4);

    void drawcircles_thread(QPainter &p, Camera &camera, vector<Point_3d> point, vector<int> r, int xmin, int xmax, vector<double> normal);

private:
    QPainter &p;
    Camera &camera;

    Raytracing raytrace;
};

#endif // DRAW_H
