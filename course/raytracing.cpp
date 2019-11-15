#include "raytracing.h"

double Raytracing::scalar(Point_3d v1, Point_3d v2) {
    double s = v1.get_x() * v2.get_x() + v1.get_y() * v2.get_y() + v1.get_z() * v2.get_z();
    return s;
}

double Raytracing::IntersectRaySphere(Point_3d camera_pos, Point_3d point, Point_3d centr, int r) {
    double t1, t2;
    Point_3d oc(centr.get_x() - camera_pos.get_x(), centr.get_y() - camera_pos.get_y(), centr.get_z() - camera_pos.get_z());
    Point_3d d(point.get_x() - camera_pos.get_x(), point.get_y() - camera_pos.get_y(), point.get_z() - camera_pos.get_z());


    double k1 = scalar(d, d);
    double k2 = scalar(oc, d);
    double k3 = scalar(oc, oc) - r * r;

    double discriminant = k2 * k2 - k1 * k3;
    if (discriminant < 0)
        return 0;

    discriminant = sqrt(discriminant);
    t1 = (k2 + discriminant) / k1;
    t2 = (k2 - discriminant) / k1;
    if (t1 < 0)
        return t2;
    if (t2 < 0)
        return t1;

    return min(t1, t2);
}

double Raytracing::IntersectRayPlane(Point_3d camera_pos, Point_3d point, vector<double> normal) {
    Point_3d d(point.get_x() - camera_pos.get_x(), point.get_y() - camera_pos.get_y(), point.get_z() - camera_pos.get_z());
    double dn = scalar(d, Point_3d(normal[0], normal[1], normal[2]));

    if (fabs(dn) > 0.001) {
        return (normal[3] - scalar(camera_pos, Point_3d(normal[0], normal[1], normal[2]))) / dn;
    }
    return 0;
}

QColor Raytracing::TraceRay(Camera camera, Point_3d point, vector<Point_3d> centr, vector<int> r, vector<double> normal) {
    Point_3d cam(camera.get_position().get_x(), camera.get_position().get_y(), camera.get_position().get_z());
    double closest_t = 10000;
    QColor closest = Qt::white;

    double t2 = IntersectRayPlane(cam, point, normal);
    if (t2 > 0 && t2 < closest_t) {
        closest_t = t2;
        closest = Qt::gray;
    }

    for (int i = 0; i < centr.size(); i++) {
        double t1 = IntersectRaySphere(cam, point, centr[i], r[i]);
        if (t1 > 0 && t1 < closest_t) {
            closest_t = t1;
            closest = Qt::red;
        }
    }

    return closest;
}
