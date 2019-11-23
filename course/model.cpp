#include "model.h"
#include <QDebug>

Model::Model(vector<Particle> particles) {
    this->particles = particles;
}

void Model::add_particle(Particle particle) {
    particles.push_back(particle);
}

vector<Particle> Model::get_particles() {
    return particles;
}

vector<Particle> &Model::get_var_particles() {
    return particles;
}

int Model::get_kol_particles() {
    return int(particles.size());
}

vector<Point_3d> Model::get_ground() {
    return vector<Point_3d>{p1, p2, p3};
}

void Model::set_ground(vector<Point_3d> points) {
    p1 = points[0];
    p2 = points[1];
    p3 = points[2];
}

Particle Model::get_main() {
    return main;
}

void Model::set_main(Particle main) {
    this->main = main;
}

//*****************************************************************************
//   This program is a 'remote' 3D-collision detector for two balls on linear
//   trajectories and returns, if applicable, the location of the collision for
//   both balls as well as the new velocity vectors (assuming a partially elastic
//   collision as defined by the restitution coefficient).
//   The equations on which the code is based have been derived at
//   http://www.plasmaphysics.org.uk/collision3d.htm
//
//   All variables apart from 'error' are of Double Precision Floating Point type.
//
//   The Parameters are:
//
//    R    (restitution coefficient)  between 0 and 1 (1=perfectly elastic collision)
//    m1    (mass of ball 1)
//    m2    (mass of ball 2)
//    r1    (radius of ball 1)
//    r2    (radius of ball 2)
//  & x1    (x-coordinate of ball 1)
//  & y1    (y-coordinate of ball 1)
//  & z1    (z-coordinate of ball 1)
//  & x2    (x-coordinate of ball 2)
//  & y2    (y-coordinate of ball 2)
//  & z2    (z-coordinate of ball 2)
//  & vx1   (velocity x-component of ball 1)
//  & vy1   (velocity y-component of ball 1)
//  & vz1   (velocity z-component of ball 1)
//  & vx2   (velocity x-component of ball 2)
//  & vy2   (velocity y-component of ball 2)
//  & vz2   (velocity z-component of ball 2)
//  & error (int)     (0: no error
//                     1: balls do not collide
//                     2: initial positions impossible (balls overlap))
//
//   Note that the parameters with an ampersand (&) are passed by reference,
//   i.e. the corresponding arguments in the calling program will be updated
//   (the positions and velocities however only if 'error'=0).
//   All variables should have the same data types in the calling program
//   and all should be initialized before calling the function.
//
//   This program is free to use for everybody. However, you use it at your own
//   risk and I do not accept any liability resulting from incorrect behaviour.
//   I have tested the program for numerous cases and I could not see anything
//   wrong with it but I can not guarantee that it is bug-free under any
//   circumstances.
//
//   I would appreciate if you could report any problems to me
//   (for contact details see  http://www.plasmaphysics.org.uk/feedback.htm ).
//
//   Thomas Smid   February 2004
//                 December 2005 (a few minor changes to improve speed)
//                 December 2009 (generalization to partially inelastic collisions)
//                 July     2011 (fix for possible rounding errors)
//******************************************************************************


void collision3D(double R, double m1, double m2, double r1, double r2,
                     double x1, double y1,double z1,
                     double x2, double y2, double z2,
                     double& vx1, double& vy1, double& vz1,
                     double& vx2, double& vy2, double& vz2,
                     int& error)     {


   double r12,m21,d,v,theta2,phi2,st,ct,sp,cp,vx1r,vy1r,vz1r,fvz1r,
           thetav,phiv,dr,alpha,beta,sbeta,cbeta,a,dvz2,
           vx2r,vy2r,vz2r,x21,y21,z21,vx21,vy21,vz21,vx_cm,vy_cm,vz_cm;

   error = 0;
   r12 = r1 + r2;
   m21 = m2 / m1;
   x21 = x2 - x1;
   y21 = y2 - y1;
   z21 = z2 - z1;
   vx21 = vx2 - vx1;
   vy21 = vy2 - vy1;
   vz21 = vz2 - vz1;

   vx_cm = (m1 * vx1 + m2 * vx2) / (m1 + m2);
   vy_cm = (m1 * vy1 + m2 * vy2) / (m1 + m2);
   vz_cm = (m1 * vz1 + m2 * vz2) / (m1 + m2);

   d = sqrt(x21 * x21 + y21 * y21 + z21 * z21);
   v = sqrt(vx21 * vx21 + vy21 * vy21 + vz21 * vz21);

   if (d > r12) {
       error = 2;
       return;
   }

   if (v <= 0.0000001) {
       error = 1;
       return;
   }

   x2 = x21;
   y2 = y21;
   z2 = z21;

   vx1 = -vx21;
   vy1 = -vy21;
   vz1 = -vz21;

   theta2 = acos(z2 / d);
   if (fabs(x2) < 0.0000001 && fabs(y2) < 0.0000001) {
       phi2 = 0;
   } else {
       phi2 = atan2(y2, x2);
   }
   st = sin(theta2);
   ct = cos(theta2);
   sp = sin(phi2);
   cp = cos(phi2);

   vx1r = ct * cp * vx1 + ct * sp * vy1 - st * vz1;
   vy1r = cp * vy1 - sp * vx1;
   vz1r = st * cp * vx1 + st * sp * vy1 + ct * vz1;
   fvz1r = vz1r / v;
   if (fvz1r > 1) {
       fvz1r = 1;
   } else if (fvz1r < -1) {
       fvz1r = -1;
   }

   thetav = acos(fvz1r);
   if (fabs(vx1r) < 0.0000001 && fabs(vy1r) < 0.0000001) {
       phiv = 0;
   } else {
       phiv = atan2(vy1r, vx1r);
   }

   dr = d * sin(thetav) / r12;

   if (thetav > (M_PI / 2) || fabs(dr) > 1) {
       x2 += x1;
       y2 += y1;
       z2 += z1;
       vx1 += vx2;
       vy1 += vy2;
       vz1 += vz2;

       error = 1;
       return;
    }

   alpha = asin(-dr);
   beta = phiv;
   sbeta = sin(beta);
   cbeta = cos(beta);

   a = tan(thetav+alpha);

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

   vx1 = (vx1-vx_cm) * R + vx_cm;
   vy1 = (vy1-vy_cm) * R + vy_cm;
   vz1 = (vz1-vz_cm) * R + vz_cm;
   vx2 = (vx2-vx_cm) * R + vx_cm;
   vy2 = (vy2-vy_cm) * R + vy_cm;
   vz2 = (vz2-vz_cm) * R + vz_cm;
}

void Model::explosion(Point_3d speed) {
    if (main.get_v().get_x() < 0.001 && main.get_v().get_y() < 0.001 && main.get_v().get_z() < 0.001) {
        main.set_v(speed);
    }

    vector<Particle> copy_particles;
    copy_particles.push_back(main);
    copy_particles.insert(copy_particles.end(), particles.begin(), particles.end());

    for (size_t i = 0; i < copy_particles.size() - 1; i++) {
        for (size_t j = i + 1; j < copy_particles.size(); j++) {
            double x1 = copy_particles[i].get_p().get_x();
            double y1 = copy_particles[i].get_p().get_y();
            double z1 = copy_particles[i].get_p().get_z();
            double x2 = copy_particles[j].get_p().get_x();
            double y2 = copy_particles[j].get_p().get_y();
            double z2 = copy_particles[j].get_p().get_z();

            double vx1 = copy_particles[i].get_v().get_x();
            double vy1 = copy_particles[i].get_v().get_y();
            double vz1 = copy_particles[i].get_v().get_z();
            double vx2 = copy_particles[j].get_v().get_x();
            double vy2 = copy_particles[j].get_v().get_y();
            double vz2 = copy_particles[j].get_v().get_z();

            int error = 0;

            collision3D(1, copy_particles[i].get_m(), copy_particles[j].get_m(), copy_particles[i].get_r(), copy_particles[j].get_r(), x1, y1, z1, x2, y2, z2, vx1, vy1, vz1, vx2, vy2, vz2, error);

            copy_particles[i].set_v(Point_3d(vx1, vy1, vz1));
            copy_particles[j].set_v(Point_3d(vx2, vy2, vz2));
        }
    }

    main.set_v(copy_particles[0].get_v());
    for (size_t i = 0; i < particles.size(); i++) {
        particles[i].set_v(copy_particles[i + 1].get_v());
    }

    for (size_t i = 0; i < particles.size(); i++) {
        particles[i].set_p(Point_3d(particles[i].get_p().get_x() + particles[i].get_v().get_x() * 2, particles[i].get_p().get_y() + particles[i].get_v().get_y() * 2, particles[i].get_p().get_z() + particles[i].get_v().get_z() * 2));
    }
    main.set_p(Point_3d(main.get_p().get_x() + main.get_v().get_x() * 2, main.get_p().get_y() + main.get_v().get_y() * 2, main.get_p().get_z() + main.get_v().get_z() * 2));
}
