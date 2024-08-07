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
        } else if (state == enemy_state::charge) {
            update_charge(world_state);
        } else if (state == enemy_state::trapped_player) {
            update_trap_player(world_state);
        } else if (state == enemy_state::bonk) {
            update_bonk(world_state);
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
        if (distance_squared > get_attack_distance_squared()) {
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
            enter_attack();
        }
    }

    void world_object_enemy::enter_attack() {
        state = enemy_state::attack;

        attack_windup = get_windup_duration();

        if (type->attack_animation) play_animation(type->attack_animation.value());
        else stop_animation();
    }

    void world_object_enemy::update_attack(sp::world_state& world_state) {
        attack_windup--;

        if (attack_windup == 0) {
            if (type->behaviour_type == behaviour_type::melee) {
                vec3 to_player = world_state.get_player().get_position() - position;
                // TODO: Rather than check distance, we could do a collider-based check?
                if (to_player.magnitude_squared() < 30*30) {
                    world_state.get_player().receive_attack(world_state, type->stats);
                }
            } else if (type->behaviour_type == behaviour_type::ranged) {
                vec3 spawn_position = position + vec3::right * 9 + vec3::up * 9;
                vec3 to_player = world_state.get_player().get_position() - spawn_position;
                world_state.spawn_projectile(world_object_projectile(spawn_position, normalise(to_player) * 2));
            } else if (type->behaviour_type == behaviour_type::charger) {
                vec3 to_player = world_state.get_player().get_position() - position;
                charge_vector = normalise(to_player) * 3;
                state = enemy_state::charge;
            } else if (type->behaviour_type == behaviour_type::trapper) {
                vec3 to_player = world_state.get_player().get_position() - position;
                if (to_player.magnitude_squared() < 30*30) {
                    state = enemy_state::trapped_player;
                }
            }
        }

        // Cooldown period
        if (attack_windup == -50) {
            state = enemy_state::chase;
        }
    }

    void world_object_enemy::update_charge(sp::world_state& world_state) {
        if (type->attack_loop_animation) use_animation("charge", type->attack_loop_animation.value());

        if (world_state.get_player().get_collider().touches(get_collider())) {
            world_state.get_player().receive_attack(world_state, type->stats);
            enter_bonk();
            return;
        }

        vec3 delta = test_movement(world_state, charge_vector);
        if (delta == vec3::zero) {
            enter_bonk();
            return;
        }

        position = position + delta;

        if (sprite) {
            bool is_left_facing = delta.dot(world_state.get_camera().get_right_axis()) > 0;
            sprite->set_horizontal_flip(is_left_facing);
        }
    }

    void world_object_enemy::enter_bonk() {
        stop_animation();
        if (type->attack_end_animation) play_animation(type->attack_end_animation.value());
        attack_windup = 80;
        state = enemy_state::bonk;
    }

    void world_object_enemy::update_bonk(sp::world_state& world_state) {
        if (!animation && sprite) sprite->set_tiles(sprite_item->tiles_item());

        if (--attack_windup == 0) state = enemy_state::idle;
    }

    void world_object_enemy::update_trap_player(sp::world_state& world_state) {
        if (type->attack_loop_animation) use_animation("entrapment", type->attack_loop_animation.value());
    }

    int world_object_enemy::get_windup_duration() const {
        switch (type->behaviour_type) {
            case behaviour_type::ranged: return 10;
            case behaviour_type::charger: return 60;
            case behaviour_type::trapper: return 30;
            default:
            case behaviour_type::melee: return 30;
        }
    }

    int world_object_enemy::get_attack_distance_squared() const {
        switch (type->behaviour_type) {
            case behaviour_type::ranged: return 75*75;
            case behaviour_type::charger: return 75*75;
            case behaviour_type::trapper: return 25*25;
            default:
            case behaviour_type::melee: return 25*25;
        }
    }
}
