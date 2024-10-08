#include "world_state.h"

#include "bn_string.h"
#include "bn_log.h"

#include "wall_generator.h"
#include "world_object_wall.h"
#include "zones.h"
#include "advikku_global.h"
#include "fyingde.h"

#include "bn_sprite_items_statue.h"
#include "bn_sprite_items_npc_classmate01.h"
#include "bn_sprite_items_npc_classmate02.h"
#include "bn_sprite_items_npc_classmate03.h"
#include "bn_sprite_items_npc_classmate04.h"
#include "bn_sprite_items_npc_classmate05.h"
#include "common_variable_8x8_sprite_font.h"
#include "sp_zone_s_c1.h"
#include "sp_zone_sw_n.h"
#include "sp_zone_gym.h"

namespace sp {
    world_state::world_state() :
        small_text_generator(common::variable_8x8_sprite_font),
        is_visible(false)
    {
        small_text_generator.set_bg_priority(0);

        load_zone(sp::zone_s_c1::zone);
    }

    const world_zone& world_state::get_current_zone() const { return *current_zone; }
    bool world_state::is_final_zone() const { return current_zone == get_zone_by_name("gym"); }
    world_camera& world_state::get_camera() { return camera; }
    world_object_player& world_state::get_player() { return player; }
    bn::ivector<world_object_wall>& world_state::get_walls() { return walls; }
    bn::ivector<world_object_enemy>& world_state::get_enemies() { return enemies; }
    bn::ivector<world_object_chest>& world_state::get_chests() { return chests; }
    bn::ivector<bn::fixed_rect>& world_state::get_colliders() { return colliders; }
    bn::optional<world_object_boss>& world_state::get_boss() { return boss; }

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
        if (boss) {
            boss->update(*this);
            if (!boss->is_active()) boss.reset();
        }

        for (world_object_wall& wall : walls) {
            wall.update(*this);
        }
        for (world_object_chest& chest : chests) {
            chest.update(*this);
        }
        for (world_object_prop& prop : props) {
            prop.update(*this);
        }

        for (auto iter = callouts.begin(); iter < callouts.end(); iter++) {
            iter->update();

            if (iter->is_done()) callouts.erase(iter);
        }

        for (auto iter = projectiles.begin(); iter < projectiles.end(); iter++) {
            iter->update(*this);

            if (!iter->is_active()) projectiles.erase(iter);
        }
    }

    void world_state::load_zone(const world_zone& zone) {
        BN_LOG("Zone address:", &zone);
        current_zone = &zone;

        walls.clear();
        enemies.clear();
        colliders.clear();
        callouts.clear();
        chests.clear();
        props.clear();
        boss.reset();

        wall_generator generator;
        generator.generate_walls(zone, walls);
        generator.generate_colliders(zone, colliders);

        player.set_position(zone.get_player_spawn());

        for (auto& enemy_spawn : zone.get_enemy_spawns()) {
            enemies.push_back(world_object_enemy(enemy_spawn.enemy_type, vec3(enemy_spawn.x, 16, enemy_spawn.y)));
        }
        for (auto& prop_spawn : zone.get_prop_spawns()) {
            props.push_back(world_object_prop(vec3(prop_spawn.x, 16, prop_spawn.y), prop_spawn.sprite));
        }

        // Hack for the center garden statue
        if (&zone == get_zone_by_name("center")) {
            props.push_back(world_object_prop(vec3(16, 16, 0), bn::sprite_items::statue));
        }
        // First room
        if (&zone == get_zone_by_name("s_c1")) {
            props.push_back(world_object_prop(vec3(-76, 16, 32), bn::sprite_items::npc_classmate01));
            props.push_back(world_object_prop(vec3(-16, 16, 64), bn::sprite_items::npc_classmate02));
            props.push_back(world_object_prop(vec3(-70, 8, 0), bn::sprite_items::npc_classmate03));
            props.push_back(world_object_prop(vec3(-16, 16, 8), bn::sprite_items::npc_classmate04));
            props.push_back(world_object_prop(vec3(32, 16, 0), bn::sprite_items::npc_classmate05));
        }

        // Boss hack
        if (&zone == get_zone_by_name("gym")) {
            boss = world_object_boss(vec3::zero);
            cell_song_setup(FyingDeSongStruct);
        }
    }

    void world_state::create_damage_callout(bn::fixed_point point, int amount, bool is_weak) {
        callouts.push_back(fx_callout(small_text_generator, point, bn::to_string<4>(amount)));
    }

    void world_state::create_callout(bn::fixed_point point, const bn::string_view& text) {
        callouts.push_back(fx_callout(small_text_generator, point, text));
    }

    void world_state::queue_zone_change(const portal& portal) {
        queued_zone_change = &portal;
    }

    bool world_state::is_zone_change_queued() const { return queued_zone_change.has_value(); }

    void world_state::process_zone_change() {
        load_zone(*get_zone_by_name((*queued_zone_change)->target_zone_name));
        player.set_position(vec3((*queued_zone_change)->destination_x, 16, (*queued_zone_change)->destination_y));
        queued_zone_change.reset();
    }

    void world_state::respawn() {
        player.respawn();
        load_zone(*current_zone);
    }

    void world_state::cleanup() {
        walls.clear();
        enemies.clear();
        colliders.clear();
        callouts.clear();
        chests.clear();
        props.clear();
        boss.reset();

        player.cleanup();
    }

    void world_state::activate_chest(const world_object_chest& chest) {
        // Find the chest and trigger its non-const method...
        for (auto& c : chests) {
            if (&c == &chest) c.activate(*this);
        }
    }

    void world_state::spawn_projectile(world_object_projectile&& projectile) {
        projectiles.push_back(projectile);
    }
}
