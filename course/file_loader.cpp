#include "file_loader.h"

File_loader::File_loader() {
    file.open(fname);
}

File_loader::File_loader(const char *fnam) : fname(fnam) {
    file.open(fname);
}

File_loader::~File_loader() {
    if (file) {
        file.close();
    }
}

shared_ptr<Model> File_loader::load_model(Model_builder builder) {
    builder.build_model();

    double x, y, z;
    int r, m;
    int n;

    file >> n;

    if (n <= 0) {
        return nullptr;
    }

    for (int i = 0; i < n - 1; i++) {
        file >> x >> y >> z >> r >> m;
        builder.build_particle(x, y, z, r, m);
    }

    file >> x >> y >> z >> r >> m;
    builder.build_main(x, y, z, r, m);

    return builder.get_result();
}
