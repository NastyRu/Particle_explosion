#include "model_builder.h"
#include <QDebug>

void Model_builder::build_model() {
    model = make_shared<Model>();
    model->set_ground(vector<Point_3d>{Point_3d(-20, 25, 0), Point_3d(20, 25, 0), Point_3d(0, 25, 20)});
}

void Model_builder::build_particle(double x, double y, double z, int r) {
    model->add_particle(Particle(Point_3d(x, y, z), r));
}

void Model_builder::build_main(double x, double y, double z, int r) {
    model->set_main(Particle(Point_3d(x, y, z), r));
}

shared_ptr<Model> Model_builder::get_result() {
    return model;
}
