#include "model.h"

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
    if (0 == main.get_v().get_x() && 0 == main.get_v().get_y() && 0 == main.get_v().get_z()) {
        main.set_v(speed);
    }

    vector<Particle> copy_particles;
    copy_particles.push_back(main);
    copy_particles.insert(copy_particles.end(), particles.begin(), particles.end());
    for (int i = 0; i < copy_particles.size(); i++) {
        for (int j = i; j < particles.size(); j++) {

        }
    }

    main = Particle(Point_3d(main.get_p().get_x() + speed.get_x() * 2, main.get_p().get_y() + speed.get_y() * 2, main.get_p().get_z()), main.get_r() + + speed.get_z() * 2);
}
