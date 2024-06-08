#include "world_state.h"

namespace sp {
    world_state::world_state() {
        load_zone(world_zone::sandbox);
    }

    const world_zone& world_state::get_current_zone() const { return *current_zone; }
    world_camera& world_state::get_camera() { return camera; }
    world_object_player& world_state::get_player() { return player; }

    void world_state::update() {
        player.update(camera);
    }

    void world_state::load_zone(const world_zone& zone) {
        current_zone = &zone;
    }
}
