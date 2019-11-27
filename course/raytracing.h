#ifndef RAYTRACING_H
#define RAYTRACING_H

#include "matrix.h"
#include <QColor>
#include "camera.h"

class Raytracing{
public:
    double scalar(Point_3d v1, Point_3d v2);
    double len(Point_3d vec);
    double IntersectRaySphere(Point_3d camera_pos, Point_3d point, Point_3d centr, int r);
    double IntersectRayPlane(Point_3d camera_pos, Point_3d point, vector<double> normal);
    QColor TraceRay(Camera camera, Point_3d point, vector<Point_3d> centr, vector<int> r, vector<double> normal);
private:
};

#endif // RAYTRACING_H
