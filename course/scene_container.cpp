#include "scene_container.h"
#include <QDebug>

objects_iterator Scene_container::get_begin_object() {
    return objects.begin();
}

objects_iterator Scene_container::get_end_object() {
    return objects.end();
}

positions_iterator Scene_container::get_begin_position() {
    return positions.begin();
}

positions_iterator Scene_container::get_end_position() {
    return positions.end();
}

vector<shared_ptr<Object>> &Scene_container::get_objects() {
    return objects;
}

vector<shared_ptr<Position>> &Scene_container::get_positions() {
    return positions;
}

void Scene_container::add_object(shared_ptr<Object> object) {
    objects.push_back(object);
}

void Scene_container::add_position(shared_ptr<Position> position) {
    positions.push_back(position);
}

void Scene_container::set_current_camera(shared_ptr<Camera> cam) {
    for (objects_iterator i = get_begin_object(); i != get_end_object(); i++) {
        if (!(*i)->is_visible()) {
            Object *object = (*i).get();
            Camera* cam = ((Camera*)object);
            cam->is_current = 0;
        }
    }
    cam->is_current = 1;
}

 objects_iterator Scene_container::get_current_camera() {
    for (objects_iterator i = get_begin_object(); i != get_end_object(); i++) {
        if (!(*i)->is_visible()) {
            Object *object = (*i).get();
            Camera* cam = ((Camera*)object);
            if (1 == cam->is_current)
                return i;
        }
    }
}
