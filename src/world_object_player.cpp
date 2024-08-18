#include "world_object_player.h"

#include "bn_keypad.h"
#include "bn_log.h"

#include "world_state.h"
#include "world_camera.h"
#include "animations.h"

#include "bn_sprite_items_fred_sprite_sheet.h"
#include "bn_sprite_items_attack_fx.h"
#include "bn_sprite_items_interact.h"

namespace sp {
    constexpr bn::fixed speed(2);

    world_object_player::world_object_player() :
        world_object(bn::sprite_items::fred_sprite_sheet)
    {
        use_animation("idle", animations::player::idle);

        level = 1;
        stats = player_base_stats;
        health = stats.max_health;
    }

    const rpg_stats& world_object_player::get_stats() const { return stats; }
    int world_object_player::get_health() const { return health; }

    void world_object_player::update(sp::world_state& world_state) {
        world_camera& camera = world_state.get_camera();

        if (!is_trapped)
        {
            if (bn::keypad::a_pressed()) {
                auto interactable = get_interactable(world_state);
                if (interactable) {
                    (*interactable)->interact(world_state);
                    return;
                }
            }

            if (bn::keypad::left_held()) {
                facing = -1;
            } else if (bn::keypad::right_held()) {
                facing = 1;
            }
            if (sprite.has_value()) sprite->set_horizontal_flip(facing == -1);

            // Update time-based behaviours
            if (attack_cooldown > 0) attack_cooldown--;

            if (bn::keypad::b_pressed() && attack_cooldown == 0) {
                trigger_attack(world_state);
            }
            
            update_fx();

            if (speed_burst > 0) {
                speed_burst -= 0.2;
                if (speed_burst < 0) speed_burst = 0;
            }

            vec3 movement = get_movement_input(camera.get_heading()) * (speed + speed_burst);
            if (bn::keypad::r_pressed() && movement != vec3::zero && speed_burst == 0) {
                speed_burst = 5;
                play_animation(sp::animations::player::dash);
            }
            if (movement.x != 0 || movement.z != 0) {
                use_animation("run", animations::player::run);
            } else {
                use_animation("idle", animations::player::idle);
            }

            vec3 delta = test_movement(world_state, movement);
            position = position + delta;

            auto interactable = get_interactable(world_state);
            if (interactable) {
                auto screen_position = camera.to_screen((*interactable)->get_position()).to_point();
                if (!interaction_callout) {
                    interaction_callout = bn::sprite_items::interact.create_sprite(screen_position);
                    interaction_callout->set_bg_priority(0);
                }
                // If the interaction point moves, we need to ensure it is up to date
                interaction_callout->set_position(screen_position);
            } else if (interaction_callout) {
                interaction_callout.reset();
            }
        }

        world_object::update(world_state);
    }

    void world_object_player::receive_attack(sp::world_state& world_state, const rpg_stats& attacker) {
        // Grant iframes at beginning of dash
        if (speed_burst > 2) return;

        int damage = calculate_damage(attacker, stats);
        health -= damage;

        vec3 screen_position = get_screen_position(world_state.get_camera());
        world_state.create_damage_callout(screen_position.to_point(), damage, false);
    }

    void world_object_player::grant_item(sp::item_id item_id) {
        inventory.push_back(item_id);
    }

    void world_object_player::set_trapped(bool trapped) {
        is_trapped = trapped;
    }

    void world_object_player::respawn() {
        health = stats.max_health;
        is_trapped = false;
        is_visible = true;
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

    void world_object_player::trigger_attack(sp::world_state& world_state) {
        auto& camera = world_state.get_camera();
        int heading = camera.get_heading();
        vec3 right_axis(bn::degrees_lut_cos(heading), 0, bn::degrees_lut_sin(heading));
        bn::fixed_rect attack_collider((position + right_axis * facing * 10).to_point(), bn::fixed_size(24, 24));

        for (world_object_enemy& enemy : world_state.get_enemies()) {
            if (enemy.get_collider().touches(attack_collider)) {
                int was_alive = enemy.get_health() > 0;
                enemy.receive_attack(world_state, stats);

                // Did we land a killing blow?
                if (was_alive && enemy.get_health() <= 0) {
                    if (apply_xp(enemy.get_xp_reward())) {
                        vec3 screen_position = get_screen_position(world_state.get_camera()) + vec3::forward * 20 - vec3::right * 25;
                        world_state.create_callout(screen_position.to_point(), "LVL UP!");
                    }
                }
            }
        }

        auto& boss = world_state.get_boss();
        if (boss) {
            if (boss->get_collider().touches(attack_collider)) {
                boss->receive_attack(world_state, stats);
            }
        }

        play_animation(animations::player::punch);
        attack_fx = bn::sprite_items::attack_fx.create_sprite(32 * facing, 1);
        attack_fx->set_horizontal_flip(facing == -1);
        attack_fx->set_bg_priority(0);
        attack_fx_animation = animations::attack_fx::punch(*attack_fx);

        attack_cooldown = 20;
    }

    void world_object_player::update_fx() {
        if (!attack_fx_animation.has_value()) return;
        
        attack_fx->set_horizontal_flip(facing == -1);
        attack_fx->set_position(32 * facing, 1);
        attack_fx->set_visible(is_visible);
        attack_fx_animation->update();

        if (attack_fx_animation->done()) {
            attack_fx_animation.reset();
            attack_fx.reset();
        }
    }

    bool world_object_player::apply_xp(int amount) {
        xp += amount;

        int xp_required = get_xp_for_level_up(level);
        if (xp < xp_required) return false;

        // Level up!!!
        xp -= xp_required;
        level++;

        stats.max_health += get_player_health_growth(level);
        stats.attack += get_player_attack_growth(level);
        stats.defence += get_player_defence_growth(level);
        stats.speed += get_player_speed_growth(level);

        health = stats.max_health;

        return true;
    }

    bn::optional<const interactable*> world_object_player::get_interactable(sp::world_state& world_state) {
        auto collider = bn::rect(position.x.integer(), position.z.integer(), 32, 32);
        for (auto& portal : world_state.get_current_zone().get_portals()) {
            auto rect = bn::rect(portal.x + portal.width/2, portal.y - portal.height/2, portal.width, portal.height);

            if (collider.intersects(rect)) {
                return &portal;
            }
        }

        auto facing_position = position + world_state.get_camera().get_right_axis() * facing * 15;
        auto facing_collider = bn::rect(facing_position.x.integer(), facing_position.z.integer(), 16, 16);
        for (auto& chest : world_state.get_chests()) {
            if (!chest.get_is_opened() && chest.get_collider().touches(facing_collider)) {
                return &chest;
            }
        }

        return bn::nullopt;
    }
}
