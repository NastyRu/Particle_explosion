#ifndef MODEL_H
#define MODEL_H

#include "objects.h"
#include "base_draw.h"
#include "particles.h"

using namespace std;

class Model : public Visible_object
{
public:
    Model() {}
    ~Model() {}

    Model(vector<Particle> particles);

    void add_particle(Particle particle);

    vector<Particle> get_particles();

    int get_kol_particles();

    vector<Particle> &get_var_particles();
    char type() override { return 'm'; }
private:
    vector<Particle> particles;
};

#endif // MODEL_H
