#include "world_object_boss.h"

#include "world_state.h"
#include "animations.h"

#include "bn_sprite_items_boss_sheet.h"

namespace sp {
    world_object_boss::world_object_boss(vec3 _position)
        : world_object(bn::sprite_items::boss_sheet)
    {
        position = _position;

        stats = rpg_stats(100, 15, 15, 5);
        health = stats.max_health;
    }

    const rpg_stats& world_object_boss::get_stats() const { return stats; }
    int world_object_boss::get_health() const { return health; }
    int world_object_boss::get_xp_reward() const { return 100; }

    // TODO: Account for stuff like death animations playing before an enemy is marked inactive
    bool world_object_boss::is_active() const { return health > 0; }

    void world_object_boss::update(sp::world_state& world_state) {
        if (state == enemy_state::idle) {
            update_idle(world_state);
        } else if (state == enemy_state::chase) {
            update_chase(world_state);
        } else if (state == enemy_state::attack) {
            update_attack(world_state);
        } else if (state == enemy_state::charge) {
        } else if (state == enemy_state::trapped_player) {
        } else if (state == enemy_state::bonk) {
        }

        world_object::update(world_state);
    }

    void world_object_boss::receive_attack(sp::world_state& world_state, const rpg_stats& attacker) {
        int damage = calculate_damage(attacker, stats);
        health -= damage;

        vec3 screen_position = get_screen_position(world_state.get_camera());
        world_state.create_damage_callout(screen_position.to_point(), damage, false);
    }

    void world_object_boss::update_idle(sp::world_state& world_state) {
        if (is_transformed) use_animation("idle", sp::animations::boss::idle);
        else use_animation("idle_human", sp::animations::boss::idle_human);

        vec3 player_position = world_state.get_player().get_position();
        vec3 to_player = player_position - position;

        // Calculate distance using ints to avoid overflow over large distances
        int distance_squared = to_player.x.integer() * to_player.x.integer() + to_player.z.integer() * to_player.z.integer();
        if (distance_squared < 90*90) {
            if (!is_transformed) {
                play_animation(sp::animations::boss::transform);
                is_transformed = true;
                attack_windup = 60;
            }
        }
        if (is_transformed && --attack_windup <= 0) {
            state = enemy_state::chase;
        }
    }

    void world_object_boss::update_chase(sp::world_state& world_state) {
        use_animation("move", sp::animations::boss::move);

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

    void world_object_boss::enter_attack() {
        state = enemy_state::attack;

        use_melee = rng.get_int(100) > 50;
        attack_windup = get_windup_duration();

        if (use_melee) play_animation(sp::animations::boss::attack);
        else play_animation(sp::animations::boss::windup);
    }

    void world_object_boss::update_attack(sp::world_state& world_state) {
        attack_windup--;

        if (attack_windup == 0) {
            if (use_melee) {
                vec3 to_player = world_state.get_player().get_position() - position;
                if (to_player.magnitude_squared() < 40*40) {
                    world_state.get_player().receive_attack(world_state, stats);
                }
            } else {
                vec3 spawn_position = position + vec3::right * 9 + vec3::up * 9;
                vec3 to_player = world_state.get_player().get_position() - spawn_position;
                world_state.spawn_projectile(world_object_projectile(spawn_position, normalise(to_player) * 2, sp::animations::boss::ball_spin));
                play_animation(sp::animations::boss::throw_attack);
            }
        }

        // Cooldown period
        if (attack_windup == get_attack_cooldown()) {
            state = enemy_state::chase;
        }
    }

    int world_object_boss::get_windup_duration() const {
        return 30;
    }

    int world_object_boss::get_attack_distance_squared() const {
        return 35*35;
    }

    int world_object_boss::get_attack_cooldown() const {
        return -60;
    }
}

