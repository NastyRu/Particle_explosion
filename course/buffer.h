#ifndef BUFFER_H
#define BUFFER_H

#include "matrix.h"

class Zbuffer{
public:
    Zbuffer() { buffer = Matrix(700, 800, -10000); }
    ~Zbuffer() {}
    int pixel(int x, int y);
    void setz(int x, int y, int z);

private:
    Matrix buffer;
};

#endif // BUFFER_H
