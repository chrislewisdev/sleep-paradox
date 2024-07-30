#include "world_state.h"

#include "bn_string.h"
#include "bn_log.h"

#include "wall_generator.h"
#include "world_object_wall.h"

#include "common_variable_8x8_sprite_font.h"
#include "sp_zone_sample_8x8.h"
#include "sp_zone_alternate.h"
#include "sp_zone_corridor1.h"

namespace sp {
    world_state::world_state() :
        small_text_generator(common::variable_8x8_sprite_font),
        is_visible(false)
    {
        small_text_generator.set_bg_priority(0);

        load_zone(sp::zone_sample_8x8::zone);
    }

    const world_zone& world_state::get_current_zone() const { return *current_zone; }
    world_camera& world_state::get_camera() { return camera; }
    world_object_player& world_state::get_player() { return player; }
    bn::ivector<world_object_wall>& world_state::get_walls() { return walls; }
    bn::ivector<world_object_enemy>& world_state::get_enemies() { return enemies; }
    bn::ivector<bn::fixed_rect>& world_state::get_colliders() { return colliders; }

    bool world_state::get_visible() const { return is_visible; }
    void world_state::set_visible(bool visible) {
        is_visible = visible;

        if (!visible) callouts.clear();
    }

    void world_state::update() {
        player.update(*this);

        for (auto iter = enemies.begin(); iter < enemies.end(); iter++) {
            iter->update(*this);

            if (!iter->is_active()) enemies.erase(iter);
        }

        // Temp code
        // if (enemies.size() == 0) {
        //     enemies.push_back(world_object_enemy(enemy_type::cage, vec3(0, 16, 100)));
        // }

        for (world_object_wall& wall : walls) {
            wall.update(*this);
        }

        for (auto iter = callouts.begin(); iter < callouts.end(); iter++) {
            iter->update();

            if (iter->is_done()) callouts.erase(iter);
        }

        /*if (queued_zone_change.has_value()) {
            load_zone((*queued_zone_change)->target_zone);
            player.set_position(vec3((*queued_zone_change)->destination_x, 16, (*queued_zone_change)->destination_y));
            queued_zone_change.reset();
        }*/
    }

    void world_state::load_zone(const world_zone& zone) {
        BN_LOG("Zone address:", &zone);
        current_zone = &zone;

        walls.clear();
        enemies.clear();
        colliders.clear();
        callouts.clear();

        wall_generator generator;
        generator.generate_walls(zone, walls);
        generator.generate_colliders(zone, colliders);

        player.set_position(zone.get_player_spawn());

        for (auto enemy_spawn : zone.get_enemy_spawns()) {
            enemies.push_back(world_object_enemy(enemy_spawn.enemy_type, vec3(enemy_spawn.x, 16, enemy_spawn.y)));
        }
    }

    void world_state::create_damage_callout(bn::fixed_point point, int amount, bool is_weak) {
        callouts.push_back(fx_callout(small_text_generator, point, bn::to_string<4>(amount)));
    }

    void world_state::create_callout(bn::fixed_point point, const bn::string_view& text) {
        callouts.push_back(fx_callout(small_text_generator, point, text));
    }

    /*void world_state::queue_zone_change(const portal& portal) {
        queued_zone_change = &portal;
    }*/
}
