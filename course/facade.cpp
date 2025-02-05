#include "facade.h"

Work_with_file_manager Facade::get_work_with_file_manager() {
    return work_with_file_manager;
}

Draw_manager Facade::get_draw_manager() {
    return draw_manager;
}

Transfrom_manager Facade::get_transfrom_manager() {
    return transfrom_manager;
}

Scene_container &Facade::get_scene_container() {
    return scene_container;
}

Explosion_manager &Facade::get_explosion_manager() {
    return explosion_manager;
}
