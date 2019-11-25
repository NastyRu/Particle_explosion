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

void Model::explosion(Point_3d speed) {
    if (main.get_v().get_x() < 0.001 && main.get_v().get_y() < 0.001 && main.get_v().get_z() < 0.001) {
        main.set_v(speed);
    }

    vector<Particle> copy_particles;
    copy_particles.push_back(main);
    copy_particles.insert(copy_particles.end(), particles.begin(), particles.end());

    for (size_t i = 0; i < copy_particles.size() - 1; i++) {
        for (size_t j = i + 1; j < copy_particles.size(); j++) {
            copy_particles[i].collision(copy_particles[j]);
        }
    }

    main.set_v(copy_particles[0].get_v());
    for (size_t i = 0; i < particles.size(); i++) {
        particles[i].set_v(copy_particles[i + 1].get_v());
    }

    vector<double> x(3);
    vector<double> y(3);
    vector<double> z(3);
    x[0] = p1.get_x();
    y[0] = p1.get_y();
    z[0] = p1.get_z();
    x[1] = p2.get_x();
    y[1] = p2.get_y();
    z[1] = p2.get_z();
    x[2] = p3.get_x();
    y[2] = p3.get_y();
    z[2] = p3.get_z();

    vector<double> coef(4);
    coef[3] = x[0] * (y[1] * z[2] - y[2] * z[1]) + x[1] * (y[2] * z[0] - y[0] * z[2]) + x[2] * (y[0] * z[1] - y[1] * z[0]);
    coef[0] = (y[0] * (z[1] - z[2]) + y[1] * (z[2] - z[0]) + y[2] * (z[0] - z[1]));
    coef[1] = (z[0] * (x[1] - x[2]) + z[1] * (x[2] - x[0]) + z[2] * (x[0] - x[1]));
    coef[2] = (x[0] * (y[1] - y[2]) + x[1] * (y[2] - y[0]) + x[2] * (y[0] - y[1]));

    for (size_t i = 0; i < particles.size(); i++) {
        particles[i].update(2);

        double mount;
        mount = coef[0] * particles[i].get_p().get_x() + coef[1] * particles[i].get_p().get_y() + coef[2] * particles[i].get_p().get_z() + coef[3];

        if (fabs(mount) < particles[i].get_r()) {
            particles[i].set_v(Point_3d(particles[i].get_v().get_x(), -particles[i].get_v().get_y(), particles[i].get_v().get_z()));
        }
    }
    main.update(2);
}
