#include "model_builder.h"
#include <QDebug>

void Model_builder::build_model() {
    model = make_shared<Model>();
    if (!model) {
        throw Builder_exceptions();
    }
}

void Model_builder::build_particle(double x, double y, double z) {
    if (!model) {
        throw Builder_exceptions();
    } else {
        model->add_particle(Particle(Point_3d(x, y, z)));
    }
}

shared_ptr<Model> Model_builder::get_result() {
    return model;
}
