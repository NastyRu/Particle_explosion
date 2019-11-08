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
    coef[0] = (y[0] * (z[1] - z[2]) + y[1] * (z[2] - z[0]) + y[2] * (z[0] - z[1])) / coef[3];
    coef[1] = (z[0] * (x[1] - x[2]) + z[1] * (x[2] - x[0]) + z[2] * (x[0] - x[1])) / coef[3];
    coef[2] = (x[0] * (y[1] - y[2]) + x[1] * (y[2] - y[0]) + x[2] * (y[0] - y[1])) / coef[3];

    for (int x = max(0, xmin); x < min(800, xmax); x++) {
        for (int y = max(0, ymin); y < min(700, ymax); y++) {
            if (buf.pixel(x, y) == -10000) {
                buf.setz(x, y, (1 - coef[0] * x - coef[1] * y) / coef[2]);
            }
            if (buf.pixel(x, y) != 0 && (1 - coef[0] * x - coef[1] * y) / coef[2] > -1 / buf.pixel(x, y))
                buf.setz(x, y, (1 - coef[0] * x - coef[1] * y) / coef[2]);
        }
    }

    p.setPen(QPen(Qt::black));
    QBrush brush;
    brush.setColor(Qt::black);
    brush.setStyle(Qt::SolidPattern);
    QPainterPath path;
    path.addPolygon(polygon);
    p.drawPolygon(polygon);
    p.fillPath(path, brush);

    p.setPen(QPen(Qt::white));
}
