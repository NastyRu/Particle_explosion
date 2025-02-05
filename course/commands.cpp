#include "commands.h"

Command::Command(objects_iterator begin) {
    this->begin = begin;
    end = begin + 1;
}

Command::Command(objects_iterator begin, objects_iterator end) {
    this->begin = begin;
    this->end = end;
}

Load_command::Load_command(File_loader &file_loade, Model_builder &builde) :
    file_loader(file_loade), builder(builde) {
}

void Load_command:: call(Facade &facade) {
    shared_ptr<Model> model = facade.get_work_with_file_manager().loader_from_file(file_loader, builder);
    if (nullptr == model) {
        QMessageBox msgBox;
        msgBox.setText("Некорректный файл");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }

    Position pos(model->get_particles());
    facade.get_scene_container().add_position(make_shared<Position>(pos));
    facade.get_scene_container().add_object(model);
}

Draw_command::Draw_command(DrawQt &drawe, objects_iterator begin) :
    Command(begin), drawer(drawe) {
}

Draw_command::Draw_command(DrawQt &drawe, objects_iterator begin, objects_iterator end) :
    Command(begin, end), drawer(drawe) {
}

void Draw_command::call(Facade &facade) {
    facade.get_draw_manager().draw_model(drawer, begin, end);
}

Offset_command::Offset_command(double dx, double dy, double dz, objects_iterator begin, positions_iterator pos) :
    Command(begin) {
    this->dx = dx;
    this->dy = dy;
    this->dz = dz;
    this->pos = pos;
}

Offset_command::Offset_command(double dx, double dy, double dz, objects_iterator begin, objects_iterator end, positions_iterator pos) :
    Command(begin, end) {
    this->dx = dx;
    this->dy = dy;
    this->dz = dz;
    this->pos = pos;
}

void Offset_command::call(Facade &facade) {
    facade.get_transfrom_manager().offset_model(dx, dy, dz, begin, end, pos);
}

Scale_command::Scale_command(double k, objects_iterator begin, positions_iterator pos) :
    Command(begin) {
    this->k = k;
    this->pos = pos;
}

Scale_command::Scale_command(double k, objects_iterator begin, objects_iterator end, positions_iterator pos) :
    Command(begin, end) {
    this->k = k;
    this->pos = pos;
}

void Scale_command::call(Facade &facade) {
    facade.get_transfrom_manager().scale_model(k, begin, end, pos);
}

Rotate_x_command::Rotate_x_command(double angle, objects_iterator begin, positions_iterator pos) :
    Command(begin) {
    this->angle = angle;
    this->pos = pos;
}

Rotate_x_command::Rotate_x_command(double angle, objects_iterator begin, objects_iterator end, positions_iterator pos) :
    Command(begin, end) {
    this->angle = angle;
    this->pos = pos;
}

void Rotate_x_command::call(Facade &facade) {
    facade.get_transfrom_manager().rotate_x_model(angle, begin, end, pos);
}

Rotate_y_command::Rotate_y_command(double angle, objects_iterator begin, positions_iterator pos) :
    Command(begin) {
    this->angle = angle;
    this->pos = pos;
}

Rotate_y_command::Rotate_y_command(double angle, objects_iterator begin, objects_iterator end, positions_iterator pos) :
    Command(begin, end) {
    this->angle = angle;
    this->pos = pos;
}

void Rotate_y_command::call(Facade &facade) {
    facade.get_transfrom_manager().rotate_y_model(angle, begin, end, pos);
}

Rotate_z_command::Rotate_z_command(double angle, objects_iterator begin, positions_iterator pos) :
    Command(begin) {
    this->angle = angle;
    this->pos = pos;
}

Rotate_z_command::Rotate_z_command(double angle, objects_iterator begin, objects_iterator end, positions_iterator pos) :
    Command(begin, end) {
    this->angle = angle;
    this->pos = pos;
}

void Rotate_z_command::call(Facade &facade) {
    facade.get_transfrom_manager().rotate_z_model(angle, begin, end, pos);
}

Scale_camera_command::Scale_camera_command(double k, objects_iterator begin) :
    Command(begin) {
    this->k = k;
}

void Scale_camera_command::call(Facade &facade) {
    facade.get_transfrom_manager().scale_camera(k, begin);
}

Rotate_camera_command::Rotate_camera_command(double angleX, double angleY, objects_iterator begin) :
    Command(begin) {
    this->angleX = angleX;
    this->angleY = angleY;
}

void Rotate_camera_command::call(Facade &facade) {
    facade.get_transfrom_manager().rotate_camera(angleX, angleY, begin);
}

Explosion_command::Explosion_command(objects_iterator begin, objects_iterator end, Point_3d speed) :
    Command(begin, end) {
    this->speed = speed;
}

void Explosion_command::call(Facade &facade) {
    facade.get_explosion_manager().explosion(begin, end, speed);
}

