#include "world_object_player.h"

#include "bn_keypad.h"

#include "world_state.h"
#include "world_camera.h"
#include "animations.h"

#include "bn_sprite_items_fred_sprite_sheet.h"

namespace sp {
    constexpr bn::fixed speed(2);

    world_object_player::world_object_player() :
        world_object(bn::sprite_items::fred_sprite_sheet)
    {
        use_animation("idle", animations::player::idle);

        // TODO: We gotta get the player's current stats from somewhere!
        health = 10;
        stats = rpg_stats(10, 5, 10, 5);
    }

    const rpg_stats& world_object_player::get_stats() const { return stats; }

    void world_object_player::update(sp::world_state& world_state) {
        world_camera& camera = world_state.get_camera();

        if (bn::keypad::left_held()) {
            sprite->set_horizontal_flip(true);
            facing = -1;
        } else if (bn::keypad::right_held()) {
            sprite->set_horizontal_flip(false);
            facing = 1;
        }

        // TODO: We can probably clean this up some
        if (attack_cooldown > 0) attack_cooldown--;
        if (bn::keypad::b_pressed() && attack_cooldown == 0) {
            int heading = camera.get_heading();
            vec3 right_axis(bn::degrees_lut_cos(heading), 0, bn::degrees_lut_sin(heading));
            bn::fixed_rect attack_collider((position + right_axis * facing * 10).to_point(), bn::fixed_size(24, 24));

            for (world_object_enemy& enemy : world_state.get_enemies()) {
                if (enemy.get_collider().touches(attack_collider)) {
                    enemy.receive_attack(world_state, stats);
                }
            }

            play_animation(animations::player::punch);
            attack_cooldown = 30;
        }

        vec3 movement = get_movement_input(camera.get_heading()) * speed;
        if (movement.x != 0 || movement.z != 0) {
            use_animation("run", animations::player::run);
        } else {
            use_animation("idle", animations::player::idle);
        }

        vec3 delta = test_movement(world_state, movement);
        position = position + delta;

        world_object::update(world_state);
    }

    void world_object_player::receive_attack(sp::world_state& world_state, const rpg_stats& attacker) {
        int damage = calculate_damage(attacker, stats);
        //health -= damage;

        vec3 screen_position = get_screen_position(world_state.get_camera());
        world_state.create_damage_callout(screen_position.to_point(), damage, false);
    }

    vec3 world_object_player::get_movement_input(bn::fixed heading) {
        bool left = bn::keypad::left_held();
        bool right = bn::keypad::right_held();
        bool up = bn::keypad::up_held();
        bool down = bn::keypad::down_held();

        if (!left && !right && !up && !down) return vec3::zero;

        bn::fixed direction;
        if (left && up) {
            direction = heading + 45;
        } else if (left && down) {
            direction = heading + 135;
        } else if (right && up) {
            direction = heading - 45;
        } else if (right && down) {
            direction = heading - 135;
        } else if (left) {
            direction = heading + 90;
        } else if (right) {
            direction = heading - 90;
        } else if (up) {
            direction = heading;
        } else if (down) {
            direction = heading + 180;
        }

        // Clamp to [0..360]
        if (direction < 0) direction += 360;
        if (direction > 360) direction -= 360;

        return vec3(-bn::degrees_lut_sin(direction), 0, bn::degrees_lut_cos(direction));
    }
}
