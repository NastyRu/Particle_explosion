#ifndef MANAGERS_H
#define MANAGERS_H

#include "model.h"
#include "file_loader.h"
#include "iterators.h"
#include "base_draw.h"
#include "positions.h"
#include "camera.h"

class Base_manager
{
public:
    Base_manager() {}
    ~Base_manager() {}
};

class Work_with_file_manager : public Base_manager
{
public:
    Work_with_file_manager() {}
    ~Work_with_file_manager() {}

    shared_ptr<Model> loader_from_file(File_loader& file_loader, Model_builder& builder);
};

class Draw_manager : public Base_manager
{
public:
    Draw_manager() {}
    ~Draw_manager() {}

    void draw_model(Base_draw &drawer, objects_iterator begin, objects_iterator end);
    void draw_iter_model(Base_draw &drawer, Model model);
};

class Transfrom_manager : public Base_manager
{
public:
    Transfrom_manager() {}
    ~Transfrom_manager() {}

    void offset_model(double dx, double dy, double dz, objects_iterator begin, objects_iterator end, positions_iterator pos);
    void offset_iter_model(Model *model, double dx, double dy, double dz, Position &pos);

    void scale_model(double k, objects_iterator begin, objects_iterator end, positions_iterator pos);
    void scale_iter_model(Model *model, double k, Position &pos);

    void rotate_x_model(double angle, objects_iterator begin, objects_iterator end, positions_iterator pos);
    void rotate_x_iter_model(Model *model, double angle, Position &pos);

    void rotate_y_model(double angle, objects_iterator begin, objects_iterator end, positions_iterator pos);
    void rotate_y_iter_model(Model *model, double angle, Position &pos);

    void rotate_z_model(double angle, objects_iterator begin, objects_iterator end, positions_iterator pos);
    void rotate_z_iter_model(Model *model, double angle, Position &pos);

    void scale_camera(double k, objects_iterator begin);
    void rotate_camera(double angleX, double angleY, objects_iterator begin);
};

class Explosion_manager : public Base_manager
{
public:
    Explosion_manager() {}
    ~Explosion_manager() {}

    void explosion(objects_iterator begin, objects_iterator end, Point_3d speed);
    void explosion_iter(Model *model, Point_3d speed);
};

#endif // MANAGERS_H
