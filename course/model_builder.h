#ifndef MODEL_BUILDER_H
#define MODEL_BUILDER_H

#include "base_builder.h"
#include "model.h"

using namespace std;

class Model_builder : public Base_builder
{
public:
    Model_builder() {}
    ~Model_builder() override {}

    void build_model();
    void build_particle(double x, double y, double z, int r);
    void build_main(double x, double y, double z, int r);

    shared_ptr<Model> get_result();

private:
    shared_ptr<Model> model;
};

#endif // MODEL_BUILDER_H
