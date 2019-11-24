#include "particles.h"

Particle::Particle(Point_3d point, int r, int m) {
    this->point = point;
    this->m = m;
    this->radius = r;
}

Particle::Particle(Point_3d point, int r) {
    this->point = point;
    this->speed = Point_3d(0,0,0);
    this->m = 1;
    this->radius = r;
}

Particle::Particle(Point_3d point) {
    this->point = point;
    this->speed = Point_3d(0,0,0);
    this->m = 1;
    this->radius = 1;
}

void Particle::set_p(const Point_3d p) {
    point = p;
}

Point_3d Particle::get_p() const {
    return point;
}

void Particle::set_v(const Point_3d v) {
    speed = v;
}

Point_3d Particle::get_v() const {
    return speed;
}

void Particle::set_m(const double m) {
    this->m = m;
}

double Particle::get_m() const {
    return m;
}

void Particle::set_r(const int r) {
    this->radius = r;
}

int Particle::get_r() const {
    return radius;
}

void Particle::collision(Particle &p)     {

   double r12,m21,a,dvz2,
           vx2r,vy2r,vz2r;

   double r1 = this->get_r(), r2 = p.get_r();
   double m1 = this->get_m(), m2 = p.get_m();
   double x1 = this->get_p().get_x(), y1 = this->get_p().get_y(), z1 = this->get_p().get_z();
   double x2 = p.get_p().get_x(), y2 = p.get_p().get_y(), z2 = p.get_p().get_z();
   double vx1 = this->get_v().get_x(), vy1 = this->get_v().get_y(), vz1 = this->get_v().get_z();
   double vx2 = p.get_v().get_x(), vy2 = p.get_v().get_y(), vz2 = p.get_v().get_z();

   r12 = r1 + r2;
   m21 = m2 / m1;

   double x21, y21, z21, d;
   x21 = x2 - x1;
   y21 = y2 - y1;
   z21 = z2 - z1;
   d = sqrt(x21 * x21 + y21 * y21 + z21 * z21);

   double vx21, vy21, vz21, v;
   vx21 = vx2 - vx1;
   vy21 = vy2 - vy1;
   vz21 = vz2 - vz1;
   v = sqrt(vx21 * vx21 + vy21 * vy21 + vz21 * vz21);

   if (d > r12) {
       return;
   }

   if (v <= 0.0000001) {
       return;
   }

   x2 = x21;
   y2 = y21;
   z2 = z21;

   vx1 = -vx21;
   vy1 = -vy21;
   vz1 = -vz21;

   double theta, phi, st, ct, sp, cp;
   theta = acos(z2 / d);
   if (fabs(x2) < 0.0000001 && fabs(y2) < 0.0000001) {
       phi = 0;
   } else {
       phi = atan2(y2, x2);
   }
   st = sin(theta);
   ct = cos(theta);
   sp = sin(phi);
   cp = cos(phi);

   double vx1r, vy1r, vz1r, fvz1r;
   vx1r = ct * cp * vx1 + ct * sp * vy1 - st * vz1;
   vy1r = cp * vy1 - sp * vx1;
   vz1r = st * cp * vx1 + st * sp * vy1 + ct * vz1;

   fvz1r = vz1r / v;
   if (fvz1r > 1) {
       fvz1r = 1;
   } else if (fvz1r < -1) {
       fvz1r = -1;
   }

   double alpha, beta;
   if (fabs(vx1r) < 0.0000001 && fabs(vy1r) < 0.0000001) {
       beta = 0;
   } else {
       beta = atan2(vy1r, vx1r);
   }

   alpha = acos(fvz1r);
   if (alpha > (M_PI / 2)) {
       return;
   }

   double sbeta, cbeta;
   sbeta = sin(beta);
   cbeta = cos(beta);

   a = tan(2 * alpha);

   dvz2 = 2 * (vz1r + a * (cbeta * vx1r + sbeta * vy1r)) / ((1 + a * a) * (1 + m21));

   vz2r = dvz2;
   vx2r = a * cbeta * dvz2;
   vy2r = a * sbeta * dvz2;
   vz1r = vz1r - m21 * vz2r;
   vx1r = vx1r - m21 * vx2r;
   vy1r = vy1r - m21 * vy2r;

   vx1 = ct * cp * vx1r - sp * vy1r + st * cp * vz1r + vx2;
   vy1 = ct * sp * vx1r + cp * vy1r + st * sp * vz1r + vy2;
   vz1 = ct * vz1r - st * vx1r + vz2;
   vx2 = ct * cp * vx2r - sp * vy2r + st * cp * vz2r + vx2;
   vy2 = ct * sp * vx2r + cp * vy2r + st * sp * vz2r + vy2;
   vz2 = ct * vz2r - st * vx2r + vz2;

   this->set_v(Point_3d(vx1, vy1, vz1));
   p.set_v(Point_3d(vx2, vy2, vz2));
}

void Particle::update(int time) {
    point.set_x(point.get_x() + speed.get_x() * time);
    point.set_y(point.get_y() + speed.get_y() * time);
    point.set_z(point.get_z() + speed.get_z() * time);
}
