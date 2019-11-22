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

    vector<Point_3d> get_ground();
    void set_ground(vector<Point_3d> points);

    Particle get_main();
    void set_main(Particle main);

    void explosion(Point_3d speed);
private:
    vector<Particle> particles;

    Point_3d p1;
    Point_3d p2;
    Point_3d p3;

    Particle main;
};

#endif // MODEL_H
