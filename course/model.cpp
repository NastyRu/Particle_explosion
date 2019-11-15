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
