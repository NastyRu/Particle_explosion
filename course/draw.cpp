#include "draw.h"
#include <QDebug>

void DrawQt::drawline(Point_3d begin, Point_3d end) {
    vector<double> p1 = {begin.get_x(), begin.get_y(), begin.get_z(), 1};
    vector<double> p2 = camera.get_matrix() * p1;
    Point_3d first = {p2[0], p2[1], p2[2]};
    p1 = {end.get_x(), end.get_y(), end.get_z(), 1};
    p2 = camera.get_matrix() * p1;
    Point_3d second = {p2[0], p2[1], p2[2]};

    p.drawLine(first.get_x(), first.get_y(), second.get_x(), second.get_y());
}

void DrawQt::drawpoint(Point_3d point) {
    vector<double> p1 = {point.get_x(), point.get_y(), point.get_z(), 1};
    vector<double> p2 = camera.get_matrix() * p1;
    if  (p2[0] < 0 || p2[0] >= 800 || p2[1] < 0 || p2[1] >= 700) {
        return;
    }
    p.drawPoint(int(p2[0]), int(p2[1]));
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
    polygon << QPoint(p0[0], p0[1]);

    vec = {p2.get_x(), p2.get_y(), p2.get_z(), 1};
    p0 = camera.get_matrix() * vec;
    polygon << QPoint(p0[0], p0[1]);

    vec = {p3.get_x(), p3.get_y(), p3.get_z(), 1};
    p0 = camera.get_matrix() * vec;
    polygon << QPoint(p0[0], p0[1]);

    vec = {p4.get_x(), p4.get_y(), p4.get_z(), 1};
    p0 = camera.get_matrix() * vec;
    polygon << QPoint(p0[0], p0[1]);

    p.setPen(QPen(Qt::black));
    p.setBrush(QBrush(Qt::black));
    p.drawPolygon(polygon);
}

void DrawQt::drawcircles_thread(QPainter &p, Camera &camera, vector<Point_3d> point, vector<int> r, int xmin, int xmax, vector<double> normal) {
    for (int x = xmin; x < xmax; x++) {
        for (int y = 0; y < 634; y++) {
            QColor color = raytrace.TraceRay(camera, Point_3d(x, y, 0 - camera.get_position().get_z()), point, r, normal);
            data_lock.lock();
            p.setPen(color);
            p.drawPoint(x, y);
            data_lock.unlock();
        }
    }
}

void DrawQt::drawmodel(vector<Point_3d> point, vector<int> r, vector<Point_3d> ground) {
    vector<thread> threads;

    vector<Point_3d> new_point;
    for (size_t i = 0; i < point.size(); i++) {
        vector<double> vec1 = {point[i].get_x(), point[i].get_y(), point[i].get_z(), 1};
        vector<double> p1 = camera.get_matrix() * vec1;
        new_point.push_back(Point_3d(p1[0], p1[1], p1[2]));
    }

    vector<double> vec = {ground[0].get_x(), ground[0].get_y(), ground[0].get_z()};
    vector<double> p0 = camera.get_matrix() * vec;
    vector<double> x(3);
    vector<double> y(3);
    vector<double> z(3);
    x[0] = p0[0];
    y[0] = p0[1];
    z[0] = p0[2];

    vec = {ground[1].get_x(), ground[1].get_y(), ground[1].get_z()};
    p0 = camera.get_matrix() * vec;
    x[1] = p0[0];
    y[1] = p0[1];
    z[1] = p0[2];

    vec = {ground[2].get_x(), ground[2].get_y(), ground[2].get_z()};
    p0 = camera.get_matrix() * vec;
    x[2] = p0[0];
    y[2] = p0[1];
    z[2] = p0[2];

    vector<double> coef(4);
    coef[3] = x[0] * (y[1] * z[2] - y[2] * z[1]) + x[1] * (y[2] * z[0] - y[0] * z[2]) + x[2] * (y[0] * z[1] - y[1] * z[0]);
    coef[0] = (y[0] * (z[1] - z[2]) + y[1] * (z[2] - z[0]) + y[2] * (z[0] - z[1]));
    coef[1] = (z[0] * (x[1] - x[2]) + z[1] * (x[2] - x[0]) + z[2] * (x[0] - x[1]));
    coef[2] = (x[0] * (y[1] - y[2]) + x[1] * (y[2] - y[0]) + x[2] * (y[0] - y[1]));

    double len = sqrt(pow(coef[0], 2) + pow(coef[1], 2) + pow(coef[2], 2));

    coef[0] /= len;
    coef[1] /= len;
    coef[2] /= len;
    coef[3] /= len;

    int dx = 800 / 8;
    for (int i = 0; i < 8; i++) {
        threads.push_back(thread(&DrawQt::drawcircles_thread, this, ref(p), ref(camera), new_point, r, 0 + i * dx, (i + 1) * dx, coef));
    }

    for (int i = 0; i < 8; i++) {
        threads[i].join();
    }
}
