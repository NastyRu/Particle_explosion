#ifndef SCENE_CONTAINER_H
#define SCENE_CONTAINER_H

#include "objects.h"
#include "positions.h"
#include "iterators.h"
#include "camera.h"

using namespace std;

class Scene_container
{
public:
    Scene_container() {}
    ~Scene_container() {}

    objects_iterator get_begin_object();
    objects_iterator get_end_object();
    positions_iterator get_begin_position();
    positions_iterator get_end_position();

    vector<shared_ptr<Object>>& get_objects();
    vector<shared_ptr<Position>>& get_positions();

    void add_object(shared_ptr<Object>);
    void add_position(shared_ptr<Position> position);
    void set_current_camera(shared_ptr<Camera> cam);
    objects_iterator get_current_camera();
private:
    vector<shared_ptr<Object>> objects;
    vector<shared_ptr<Position>> positions;
    shared_ptr<Camera> current_camera;
};

#endif // SCENE_CONTAINER_H
