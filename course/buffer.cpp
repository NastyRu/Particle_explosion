#include "buffer.h"

int Zbuffer::pixel(int x, int y) {
    return buffer[y][x];
}

void Zbuffer::setz(int x, int y, int z) {
    buffer[y][x] = z;
}
