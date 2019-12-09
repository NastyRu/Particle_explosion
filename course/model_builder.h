#ifndef MODEL_BUILDER_H
#define MODEL_BUILDER_H

#include "model.h"
#include <QDebug>

using namespace std;

class Model_builder
{
public:
    Model_builder() {}
    ~Model_builder() {}

    void build_model();
    void build_particle(double x, double y, double z, int r, int m);
    void build_main(double x, double y, double z, int r, int m);

    shared_ptr<Model> get_result();

private:
    shared_ptr<Model> model;
};

#endif // MODEL_BUILDER_H
