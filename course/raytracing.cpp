#include "raytracing.h"
#include <QDebug>

double Raytracing::scalar(Point_3d v1, Point_3d v2) {
    double s = v1.get_x() * v2.get_x() + v1.get_y() * v2.get_y() + v1.get_z() * v2.get_z();
    return s;
}

double Raytracing::len(Point_3d vec) {
    return sqrt(pow(vec.get_x(), 2) + pow(vec.get_y(), 2) + pow(vec.get_z(), 2));
}

double Raytracing::IntersectRaySphere(Point_3d camera_pos, Point_3d d, Point_3d centr, int r) {
    double t1, t2;
    Point_3d oc(centr.get_x() - camera_pos.get_x(), centr.get_y() - camera_pos.get_y(), centr.get_z() - camera_pos.get_z());

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

double Raytracing::IntersectRayPlane(Point_3d camera_pos, Point_3d d, vector<double> normal) {
    double dn = scalar(d, Point_3d(normal[0], normal[1], normal[2]));

    if (fabs(dn) > 0.001) {
        return (normal[3] - scalar(camera_pos, Point_3d(normal[0], normal[1], normal[2]))) / dn;
    }
    return 0;
}

QColor Raytracing::TraceRay(Camera camera, Point_3d point, vector<Point_3d> centr, vector<int> r, vector<double> normal) {
    Point_3d cam(camera.get_position().get_x(), camera.get_position().get_y(), camera.get_position().get_z());
    Point_3d d(point.get_x() - cam.get_x(), point.get_y() - cam.get_y(), point.get_z() - cam.get_z());
    double closest_t = 10000;
    QColor closest = Qt::white;
    int closest_i = 0;

    double t2 = IntersectRayPlane(cam, d, normal);
    if (t2 > 0 && t2 < closest_t) {
        closest_t = t2;
        closest = Qt::gray;
    }

    for (int i = 0; i < centr.size(); i++) {
        double t1 = IntersectRaySphere(cam, d, centr[i], r[i]);
        if (t1 > 0 && t1 < closest_t) {
            closest_t = t1;
            closest_i = i;
            closest = Qt::yellow;
            if (i == centr.size() - 1)
                closest = Qt::red;
        }
    }

    Point_3d P(cam.get_x() + d.get_x() * closest_t, cam.get_y() + d.get_y() * closest_t, cam.get_z() + d.get_z() * closest_t);
    double t_max = 1;
    Point_3d L(200 - P.get_x(), 200 - P.get_y(), -100 - P.get_z());

    if (closest == Qt::white) {
        return closest;
    }

    if (closest == Qt::yellow || closest == Qt::red) {
        Point_3d N(P.get_x() - centr[closest_i].get_x(), P.get_y() - centr[closest_i].get_y(), P.get_z() - centr[closest_i].get_z());
        double length = len(P);
        N = Point_3d(N.get_x() / length, N.get_y() / length, N.get_z() / length);

        double dot = scalar(N, L);
        closest.setHsv(closest.hue(), closest.saturation(), 150);
        if (dot > 0) {
            closest.setHsv(closest.hue(), closest.saturation(), closest.value() + 100 * dot / (len(N) * len(L)));
        }
    }

    bool yes = false;
    for (int i = 0; i < centr.size(); i++) {
        double t1 = IntersectRaySphere(P, L, centr[i], r[i]);
        if (t1 > 0.01 && t1 < t_max) {
            t_max = t1;
            yes = true;
        }
    }

    if (yes) {
        closest.setHsv(closest.hue(), closest.saturation(), closest.value() - 50);
    }
    return closest;
}
