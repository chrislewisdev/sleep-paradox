#include "world_object_enemy.h"

#include "world_state.h"

#include "bn_sprite_items_bully01_side_profile.h"

namespace sp {
    world_object_enemy::world_object_enemy(const enemy_type& _type, vec3 _position)
        : world_object(_type.sprite_item), type(&_type)
    {
        position = _position;

        health = type->stats.max_health;
    }

    const rpg_stats& world_object_enemy::get_stats() const { return type->stats; }
    int world_object_enemy::get_health() const { return health; }
    int world_object_enemy::get_xp_reward() const { return type->xp_reward; }

    // TODO: Account for stuff like death animations playing before an enemy is marked inactive
    bool world_object_enemy::is_active() const { return health > 0; }

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

    void world_object_enemy::receive_attack(sp::world_state& world_state, const rpg_stats& attacker) {
        int damage = calculate_damage(attacker, type->stats);
        health -= damage;

        vec3 screen_position = get_screen_position(world_state.get_camera());
        world_state.create_damage_callout(screen_position.to_point(), damage, false);

    }

    void world_object_enemy::update_idle(sp::world_state& world_state) {
        stop_animation();

        vec3 player_position = world_state.get_player().get_position();
        vec3 to_player = player_position - position;

        // Calculate distance using ints to avoid overflow over large distances
        int distance_squared = to_player.x.integer() * to_player.x.integer() + to_player.z.integer() * to_player.z.integer();
        if (distance_squared < 90*90) {
            state = enemy_state::chase;
        }
    }

    void world_object_enemy::update_chase(sp::world_state& world_state) {
        if (type->move_animation) use_animation("move", type->move_animation.value());

        vec3 player_position = world_state.get_player().get_position();
        vec3 to_player = player_position - position;

        // Calculate distance using ints to avoid overflow over large distances
        int distance_squared = to_player.x.integer() * to_player.x.integer() + to_player.z.integer() * to_player.z.integer();
        auto attack_distance = type->behaviour_type == behaviour_type::melee ? 25*25 : 50*50;
        if (distance_squared > attack_distance) {
            // Calculated using angle to player because normalising vectors over a certain length seems buggy (yields a negative vector)
            bn::fixed angle = bn::degrees_atan2(to_player.x.integer(), to_player.z.integer());
            if (angle < 0) angle += 360;

            vec3 movement = vec3(bn::degrees_lut_sin(angle), 0, bn::degrees_lut_cos(angle));
            vec3 delta = test_movement(world_state, movement);
            position = position + delta;

            if (sprite) {
                bool is_left_facing = delta.dot(world_state.get_camera().get_right_axis()) > 0;
                sprite->set_horizontal_flip(is_left_facing);
            }
        } else {
            state = enemy_state::attack;
            // We'll probably need a nicer way to init states later on :)
            attack_windup = 30;

            if (type->attack_animation) play_animation(type->attack_animation.value());
            else stop_animation();
        }
    }

    void world_object_enemy::update_attack(sp::world_state& world_state) {
        attack_windup--;

        if (attack_windup == 0) {
            vec3 to_player = world_state.get_player().get_position() - position;
            if (type->behaviour_type == behaviour_type::melee) {
                // TODO: Rather than check distance, we could do a collider-based check?
                if (to_player.magnitude_squared() < 30*30) {
                    world_state.get_player().receive_attack(world_state, type->stats);
                }
            } else if (type->behaviour_type == behaviour_type::ranged) {
                world_state.spawn_projectile(world_object_projectile(position, normalise(to_player)));
            }
        }

        // Cooldown period
        if (attack_windup == -50) {
            state = enemy_state::chase;
        }
    }
}
