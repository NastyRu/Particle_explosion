#include "draw.h"
#include <QDebug>

int sign(double c) {
    if (c > 0)
        return 1;
    if (c < 0)
        return -1;
    return 0;
}

void DrawQt::drawline(Point_3d begin, Point_3d end) {
    Point_2d p1 = begin;
    Point_2d p2 = end;
    p.drawLine(p1.get_x(), p1.get_y(), p2.get_x(), p2.get_y());
}

void DrawQt::drawpoint(Point_3d point) {
    vector<double> p1 = {point.get_x(), point.get_y(), point.get_z(), 1};
    vector<double> p2 = camera.get_matrix() * p1;
    p.drawPoint(p2[0], p2[1]);
    if (p2[3] != 0 && sign(p2[3]) == sign(camera.get_position().get_z())) {
        p.drawPoint(p2[0], p2[1]);
    }
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
    QBrush brush;
    brush.setColor(Qt::black);
    brush.setStyle(Qt::SolidPattern);
    QPainterPath path;
    path.addPolygon(polygon);
    p.drawPolygon(polygon);
    p.fillPath(path, brush);

    p.setPen(QPen(Qt::white));
}
