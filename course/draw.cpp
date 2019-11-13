#include "draw.h"
#include <QDebug>

void DrawQt::drawline(Point_3d begin, Point_3d end) {
    Point_2d p1 = begin;
    Point_2d p2 = end;
    p.drawLine(p1.get_x(), p1.get_y(), p2.get_x(), p2.get_y());
}

void DrawQt::drawpoint(Point_3d point) {
    vector<double> p1 = {point.get_x(), point.get_y(), point.get_z(), 1};
    vector<double> p2 = camera.get_matrix() * p1;
    if  (p2[0] < 0 || p2[0] >= 800 || p2[1] < 0 || p2[1] >= 700) {
        return;
    }
    if (p2[2] > buf.pixel(p2[0], p2[1])) {
        buf.setz(p2[0], p2[1], int(p2[2]));
        p.drawPoint(int(p2[0]), int(p2[1]));
    }
}

void DrawQt::drawcircle(Point_3d point, int r) {
    vector<double> p1 = {point.get_x(), point.get_y(), point.get_z(), 1};
    vector<double> p2 = camera.get_matrix() * p1;

    p.setPen(QPen(Qt::red));
    p.setBrush(QBrush(Qt::red));
    p.drawEllipse(QPoint(p2[0], p2[1]), r, r);
}

void DrawQt::drawpolygon(Point_3d p1, Point_3d p2, Point_3d p3, Point_3d p4) {
    vector<double> vec = {p1.get_x(), p1.get_y(), p1.get_z(), 1};
    vector<double> p0 = camera.get_matrix() * vec;
    QPolygon polygon;
    vector<double> x(3);
    vector<double> y(3);
    vector<double> z(3);
    x[0] = p0[0];
    y[0] = p0[1];
    z[0] = p0[2];
    polygon << QPoint(p0[0], p0[1]);
    int xmin = p0[0];
    int xmax = p0[0];
    int ymin = p0[1];
    int ymax = p0[1];

    vec = {p2.get_x(), p2.get_y(), p2.get_z(), 1};
    p0 = camera.get_matrix() * vec;
    x[1] = p0[0];
    y[1] = p0[1];
    z[1] = p0[2];
    polygon << QPoint(p0[0], p0[1]);
    xmin = min(int(p0[0]), xmin);
    xmax = max(int(p0[0]), xmax);
    ymin = min(int(p0[1]), ymin);
    ymax = max(int(p0[1]), ymax);

    vec = {p3.get_x(), p3.get_y(), p3.get_z(), 1};
    p0 = camera.get_matrix() * vec;
    x[2] = p0[0];
    y[2] = p0[1];
    z[2] = p0[2];
    polygon << QPoint(p0[0], p0[1]);
    xmin = min(int(p0[0]), xmin);
    xmax = max(int(p0[0]), xmax);
    ymin = min(int(p0[1]), ymin);
    ymax = max(int(p0[1]), ymax);

    vec = {p4.get_x(), p4.get_y(), p4.get_z(), 1};
    p0 = camera.get_matrix() * vec;
    polygon << QPoint(p0[0], p0[1]);
    xmin = min(int(p0[0]), xmin);
    xmax = max(int(p0[0]), xmax);
    ymin = min(int(p0[1]), ymin);
    ymax = max(int(p0[1]), ymax);

    vector<double> coef(4);
    coef[3] = -x[0] * (y[1] * z[2] - y[2] * z[1]) - x[1] * (y[2] * z[0] - y[0] * z[2]) - x[2] * (y[0] * z[1] - y[1] * z[0]);
    coef[0] = (y[0] * (z[1] - z[2]) + y[1] * (z[2] - z[0]) + y[2] * (z[0] - z[1]));
    coef[1] = (z[0] * (x[1] - x[2]) + z[1] * (x[2] - x[0]) + z[2] * (x[0] - x[1]));
    coef[2] = (x[0] * (y[1] - y[2]) + x[1] * (y[2] - y[0]) + x[2] * (y[0] - y[1]));

    for (int x = max(0, xmin); x < min(800, xmax); x++) {
        for (int y = max(0, ymin); y < min(700, ymax); y++) {
            if (buf.pixel(x, y) == -10000) {
                buf.setz(x, y, (coef[3] - coef[0] * x - coef[1] * y) / coef[2]);
            }
            if (buf.pixel(x, y) != 0 && (1 - coef[0] * x - coef[1] * y) / coef[2] > -1 / buf.pixel(x, y))
                buf.setz(x, y, (coef[3] - coef[0] * x - coef[1] * y) / coef[2]);
        }
    }

    p.setPen(QPen(Qt::black));
    p.setBrush(QBrush(Qt::black));
    p.drawPolygon(polygon);
}

double scalar(Point_3d v1, Point_3d v2) {
    double s = v1.get_x() * v2.get_x() + v1.get_y() * v2.get_y() + v1.get_z() * v2.get_z();
    return s;
}

double IntersectRaySphere(Point_3d camera_pos, Point_3d point, Point_3d centr, int r) {
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

double IntersectRayPlane(Point_3d camera_pos, Point_3d point, vector<double> normal) {
    Point_3d d(point.get_x() - camera_pos.get_x(), point.get_y() - camera_pos.get_y(), point.get_z() - camera_pos.get_z());
    double dn = scalar(d, Point_3d(normal[0], normal[1], normal[2]));

    if (fabs(dn) > 0.001) {
        return (normal[3] - scalar(camera_pos, Point_3d(normal[0], normal[1], normal[2]))) / dn;
    }
    return 0;
}

QColor TraceRay(Camera camera, Point_3d point, vector<Point_3d> centr, vector<int> r, vector<double> normal) {
    Point_3d cam(camera.get_position().get_x(), camera.get_position().get_y(), camera.get_position().get_z());
    double closest_t = 10000;
    QColor closest = Qt::white;

    for (int i = 0; i < centr.size(); i++) {
        double t1 = IntersectRaySphere(cam, point, centr[i], r[i]);
        double t2 = IntersectRayPlane(cam, point, normal);

        if (t1 > 0 && t1 < closest_t) {
            closest_t = t1;
            closest = Qt::red;
        }
        if (t2 > 0 && t2 < closest_t) {
            closest_t = t2;
            closest = Qt::black;
        }
    }

    return closest;
}

void drawcircles_thread(QPainter &p, Camera &camera, vector<Point_3d> point, vector<int> r, int xmin, int xmax, vector<double> normal) {
    for (int x = xmin; x < xmax; x++) {
        for (int y = 0; y < 600; y++) {
            QColor color = TraceRay(camera, Point_3d(x, y, 0 - camera.get_position().get_z()), point, r, normal);
            data_lock.lock();
            p.setPen(color);
            p.drawPoint(x, y);
            data_lock.unlock();
        }
    }
}

void DrawQt::drawcircles(vector<Point_3d> point, vector<int> r) {
    vector<thread> threads;

    vector<Point_3d> new_point;
    for (int i = 0; i < point.size(); i++) {
        vector<double> vec1 = {point[i].get_x(), point[i].get_y(), point[i].get_z(), 1};
        vector<double> p1 = camera.get_matrix() * vec1;
        new_point.push_back(Point_3d(p1[0], p1[1], p1[2]));
    }

    vector<double> vec = {-300, 200, 0, 1};
    vector<double> p0 = camera.get_matrix() * vec;
    vector<double> x(3);
    vector<double> y(3);
    vector<double> z(3);
    x[0] = p0[0];
    y[0] = p0[1];
    z[0] = p0[2];

    vec = {500, 200, 0, 1};
    p0 = camera.get_matrix() * vec;
    x[1] = p0[0];
    y[1] = p0[1];
    z[1] = p0[2];

    vec = {500, 200, 600, 1};
    p0 = camera.get_matrix() * vec;
    x[2] = p0[0];
    y[2] = p0[1];
    z[2] = p0[2];

    vector<double> coef(4);
    coef[3] = -x[0] * (y[1] * z[2] - y[2] * z[1]) - x[1] * (y[2] * z[0] - y[0] * z[2]) - x[2] * (y[0] * z[1] - y[1] * z[0]);
    coef[0] = (y[0] * (z[1] - z[2]) + y[1] * (z[2] - z[0]) + y[2] * (z[0] - z[1]));
    coef[1] = (z[0] * (x[1] - x[2]) + z[1] * (x[2] - x[0]) + z[2] * (x[0] - x[1]));
    coef[2] = (x[0] * (y[1] - y[2]) + x[1] * (y[2] - y[0]) + x[2] * (y[0] - y[1]));

    double len = sqrt(pow(coef[0], 2) + pow(coef[1], 2) + pow(coef[2], 2));

    coef[0] /= len;
    coef[1] /= len;
    coef[2] /= len;
    coef[3] /= -len;

    int dx = 800 / 32;
    for (int i = 0; i < 32; i++) {
        threads.push_back(thread(drawcircles_thread, ref(p), ref(camera), new_point, r, 0 + i * dx, (i + 1) * dx, coef));
    }

    for (int i = 0; i < 32; i++) {
        threads[i].join();
    }
}
