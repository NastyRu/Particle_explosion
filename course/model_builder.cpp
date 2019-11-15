#include "model_builder.h"
#include <QDebug>

void Model_builder::build_model() {
    model = make_shared<Model>();
    if (!model) {
        throw Builder_exceptions();
    }
    model->set_ground(vector<Point_3d>{Point_3d(-300, 200, 0), Point_3d(500, 200, 0), Point_3d(500, 200, 600)});
}

void Model_builder::build_particle(double x, double y, double z, int r) {
    if (!model) {
        throw Builder_exceptions();
    } else {
        model->add_particle(Particle(Point_3d(x, y, z), r));
    }
}

shared_ptr<Model> Model_builder::get_result() {
    return model;
}
