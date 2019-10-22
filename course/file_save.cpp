#include "file_save.h"
#include <QDebug>

File_save::File_save() {
    file.open(fname);
    if (!file) {
        throw Work_with_file_exceptions();
    }
}

File_save::File_save(const char *fnam) : fname(fnam) {
    file.open(fname);
    if (!file) {
        throw Work_with_file_exceptions();
    }
}

File_save::~File_save() {
    if (file) {
        file.close();
    }
}

void File_save::save_model(shared_ptr<Model> model) {
    int np = model->get_kol_particles();
    vector<Particle> particles = model->get_particles();

    file << np << endl;
    for (int i = 0; i < np; i++) {
        Point_3d p = particles[i].get_p();
        file << p.get_x() << " " << p.get_y() << " " << p.get_z() << endl;
    }
}
