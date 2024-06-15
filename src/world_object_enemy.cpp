#include "world_object_enemy.h"

#include "bn_log.h"

#include "world_state.h"

#include "bn_sprite_items_bully01_side_profile.h"

namespace sp {
    world_object_enemy::world_object_enemy(vec3 _position)
        : world_object(bn::sprite_items::bully01_side_profile)
    {
        position = _position;
    }

    void world_object_enemy::update(sp::world_state& world_state) {
        if (state == enemy_state::idle) {
            update_idle(world_state);
        } else if (state == enemy_state::chase) {
            update_chase(world_state);
        } else if (state == enemy_state::attack) {
            update_attack(world_state);
        }

        world_object::update(world_state);
    }

    void world_object_enemy::update_idle(sp::world_state& world_state) {
        vec3 player_position = world_state.get_player().get_position();
        bn::fixed player_distance = (player_position - position).magnitude();

        if (player_distance < 90) {
            state = enemy_state::chase;
        }
    }

    void world_object_enemy::update_chase(sp::world_state& world_state) {
        vec3 player_position = world_state.get_player().get_position();
        vec3 to_player = player_position - position;

        // Calculate distance using ints to avoid overflow over large distances
        int distance_squared = to_player.x.integer() * to_player.x.integer() + to_player.z.integer() * to_player.z.integer();
        if (distance_squared > 25*25) {
            // Calculated using angle to player because normalising vectors over a certain length seems buggy (yields a negative vector)
            bn::fixed angle = bn::degrees_atan2(to_player.x.integer(), to_player.z.integer());
            if (angle < 0) angle += 360;

            vec3 movement = vec3(bn::degrees_lut_sin(angle), 0, bn::degrees_lut_cos(angle));
            vec3 delta = test_movement(world_state, movement);
            position = position + delta;
        } else {
            //state = enemy_state::attack;
        }
    }

    void world_object_enemy::update_attack(sp::world_state& world_state) {

    }
}
