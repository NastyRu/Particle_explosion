#include "managers.h"

shared_ptr<Model> Work_with_file_manager::loader_from_file(File_loader &file_loader, Model_builder &builder) {
    return file_loader.load_model(builder);
}

void Draw_manager::draw_model(Base_draw &drawer, objects_iterator begin, objects_iterator end) {
    for (objects_iterator i = begin; i != end; i++) {
        if ((*i)->is_visible()) {
            Object* object = (*i).get();
            Visible_object* vobject = (Visible_object*)object;
            char c = vobject->type();
            switch (c) {
                case 'm': {
                    Model model = *((Model*)object);
                    draw_iter_model(drawer, model);
                    break;
                }
            }

        }
    }
}

void Draw_manager::draw_iter_model(Base_draw &drawer, Model model) {
    vector<Particle> particles = model.get_particles();
    vector<Point_3d> point;
    vector<int> r;
    for (int i = 0; i < model.get_kol_particles(); i++) {
        Point_3d p = particles[i].get_p();
        point.push_back(particles[i].get_p());
        r.push_back(particles[i].get_r());

    }
    drawer.drawmodel(point, r, model.get_ground());
}

void Transfrom_manager::offset_model(double dx, double dy, double dz, objects_iterator begin, objects_iterator end, positions_iterator pos) {
    for (objects_iterator i = begin; i != end; i++, pos++) {
        if ((*i)->is_visible()) {
            Object* object = (*i).get();
            Model* model = ((Model*)object);
            offset_iter_model(model, dx, dy, dz, *(*pos).get());
        }
    }
}

void Transfrom_manager::offset_iter_model(Model *model, double dx, double dy, double dz, Position &pos) {
    for (int i = 0; i < model->get_kol_particles(); i++) {
        Point_3d p = model->get_var_particles()[i].get_p();
        p.offset(dx, dy, dz);
        model->get_var_particles()[i].set_p(p);
    }
    pos.get_center().offset(dx, dy, dz);
}

void Transfrom_manager::scale_model(double k, objects_iterator begin, objects_iterator end, positions_iterator pos) {
    for (objects_iterator i = begin; i != end; i++, pos++) {
        if ((*i)->is_visible()) {
            Object* object = (*i).get();
            Model* model = ((Model*)object);
            scale_iter_model(model, k, *(*pos).get());
        }
    }
}

void Transfrom_manager::scale_iter_model(Model *model, double k, Position &pos) {
    for (int i = 0; i < model->get_kol_particles(); i++) {
        Point_3d p = model->get_var_particles()[i].get_p();
        p.scale(k, pos.get_center());
        model->get_var_particles()[i].set_p(p);
    }
}

void Transfrom_manager::rotate_x_model(double angle, objects_iterator begin, objects_iterator end, positions_iterator pos) {
    for (objects_iterator i = begin; i != end; i++, pos++) {
        if ((*i)->is_visible()) {
            Object* object = (*i).get();
            Model* model = ((Model*)object);
            rotate_x_iter_model(model, angle, *(*pos).get());
        }
    }
}

void Transfrom_manager::rotate_x_iter_model(Model *model, double angle, Position &pos) {
    for (int i = 0; i < model->get_kol_particles(); i++) {
        Point_3d p = model->get_var_particles()[i].get_p();
        p.rotate_x(angle, pos.get_center());
        model->get_var_particles()[i].set_p(p);
    }
}

void Transfrom_manager::rotate_y_model(double angle, objects_iterator begin, objects_iterator end, positions_iterator pos) {
    for (objects_iterator i = begin; i != end; i++, pos++) {
        if ((*i)->is_visible()) {
            Object* object = (*i).get();
            Model* model = ((Model*)object);
            rotate_y_iter_model(model, angle, *(*pos).get());
        }
    }
}

void Transfrom_manager::rotate_y_iter_model(Model *model, double angle, Position &pos) {
    for (int i = 0; i < model->get_kol_particles(); i++) {
        Point_3d p = model->get_var_particles()[i].get_p();
        p.rotate_y(angle, pos.get_center());
        model->get_var_particles()[i].set_p(p);
    }
}

void Transfrom_manager::rotate_z_model(double angle, objects_iterator begin, objects_iterator end, positions_iterator pos) {
    for (objects_iterator i = begin; i != end; i++, pos++) {
        if ((*i)->is_visible()) {
            Object* object = (*i).get();
            Model* model = ((Model*)object);
            rotate_z_iter_model(model, angle, *(*pos).get());
        }
    }
}

void Transfrom_manager::rotate_z_iter_model(Model *model, double angle, Position &pos) {
    for (int i = 0; i < model->get_kol_particles(); i++) {
        Point_3d p = model->get_var_particles()[i].get_p();
        p.rotate_z(angle, pos.get_center());
        model->get_var_particles()[i].set_p(p);
    }
}

void Transfrom_manager::scale_camera(double k, objects_iterator begin) {
    Object *object = (*begin).get();
    Camera* camera = ((Camera*)object);
    camera->scale(k);
}

void Transfrom_manager::rotate_camera(double angleX, double angleY, objects_iterator begin) {
    Object *object = (*begin).get();
    Camera* camera = ((Camera*)object);
    camera->rotation(angleX, angleY);
}

void Explosion_manager::explosion(objects_iterator begin, objects_iterator end, Point_3d pos) {
    for (objects_iterator i = begin; i != end; i++) {
        if ((*i)->is_visible()) {
            Object* object = (*i).get();
            Model* model = ((Model*)object);
            if (model->type() == 'm') {
                explosion_iter(model, pos);
            }
        }
    }
}

void Explosion_manager::explosion_iter(Model *model, Point_3d &pos) {
    for (int i = 0; i < model->get_kol_particles(); i++) {
        Point_3d p = model->get_var_particles()[i].get_p();
        Point_3d p2;
        double d = 100.0;

        if (pos.get_x() < p.get_x()) {
            p2.set_x(p.get_x() + 100);
            d /= (p.get_x() - pos.get_x());
        } else if (pos.get_x() > p.get_x()) {
            p2.set_x(p.get_x() - 100);
            d /= (pos.get_x() - p.get_x());
        } else {
            p2.set_x(p.get_x());
        }

        if (p.get_y() < pos.get_y()) {
            //p2.set_y(p.get_y() - 100);
            d *= (pos.get_y() - p.get_y());
            p2.set_y(p.get_y() - d);
        } else if (p.get_y() > pos.get_y()) {
            //p2.set_y(p.get_y() + 100);
            d *= (p.get_y() - pos.get_y());
            p2.set_y(p.get_y() + d);
        } else {
            p2.set_y(p.get_y() + 100);
        }
        p2.set_z(p.get_z());
        model->get_var_particles()[i].set_p(p2);
    }
}
