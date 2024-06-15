#include "world_state.h"

#include "wall_generator.h"

namespace sp {
    world_state::world_state() {
        load_zone(world_zone::sandbox);
    }

    const world_zone& world_state::get_current_zone() const { return *current_zone; }
    world_camera& world_state::get_camera() { return camera; }
    world_object_player& world_state::get_player() { return player; }
    bn::ivector<world_object_wall>& world_state::get_walls() { return walls; }
    bn::ivector<world_object_enemy>& world_state::get_enemies() { return enemies; }

    void world_state::update() {
        player.update(*this);

        for (world_object_enemy& enemy : enemies) {
            enemy.update(*this);
        }

        for (world_object_wall& wall : walls) {
            wall.update(*this);
        }
    }

    void world_state::load_zone(const world_zone& zone) {
        current_zone = &zone;

        wall_generator generator;
        generator.generate_walls(zone, walls);

        enemies.push_back(world_object_enemy(enemy_type::basic, vec3(-150, 16, 30)));
    }
}
