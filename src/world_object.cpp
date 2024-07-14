#include "world_object.h"

#include "bn_display.h"

#include "world_state.h"

namespace sp {
    // We might need different colliders for each sprite but this works for now
    constexpr bn::fixed_size collider_size(16, 16);

    world_object::world_object(const bn::sprite_item& _sprite_item)
        : position(0, 16, 0),
          sprite_item(&_sprite_item)
    {
    }

    const vec3& world_object::get_position() const {
        return position;
    }

    void world_object::set_position(const vec3& _position) {
        position = _position;
    }

    vec3 world_object::get_screen_position(const world_camera& camera) const {
        // Translation was supposed to be part of the world transform but that was broken so we just do it manually :(
        return (position - camera.get_position()) * camera.get_world_transform() * camera.get_scale();
    }

    bn::fixed_rect world_object::get_collider() const {
        return bn::fixed_rect(position.to_point(), collider_size);
    }

    void world_object::use_animation(const bn::string_view& name, animation_generator generator) {
        if (!sprite.has_value() || current_animation_name == name) return;

        current_animation_name = name;
        current_animation_generator = generator;
        
        if (!animation.has_value() || animation->update_forever()) animation = generator(*sprite);
    }

    void world_object::play_animation(animation_generator generator) {
        if (!sprite.has_value()) return;

        animation = generator(*sprite);
    }

    void world_object::update(sp::world_state& world_state) {
        vec3 screen_position = get_screen_position(world_state.get_camera());

        // Check if sprite is on/off screen
        constexpr int clip_left = -bn::display::width() / 2 - 32;
        constexpr int clip_right = bn::display::width() / 2 + 32;
        constexpr int clip_top = bn::display::height() / 2 + 32;
        constexpr int clip_bottom = -bn::display::height() / 2 - 32;
        const bool visible = world_state.get_visible() && 
            !(screen_position.x < clip_left || screen_position.x > clip_right || screen_position.z < clip_bottom || screen_position.z > clip_top);

        // Butano already filters out off-screen sprites, but by using less sprite_ptrs we save on sorting layers
        if (!visible && sprite.has_value()) {
            if (animation.has_value()) {
                animation.reset();
            }
            sprite.reset();
        } else if (visible && !sprite.has_value()) {
            sprite = sprite_item->create_sprite(0, 0);
            sprite->set_bg_priority(2);

            if (current_animation_generator.has_value()) {
                animation = current_animation_generator.value()(*sprite);
            }
        }

        if (sprite.has_value()) {
            sprite->set_position(screen_position.x, screen_position.z);
            // Only set sort order for visible sprites to save on sorting layers
            if (sprite->visible()) {
                sprite->set_z_order(-screen_position.z.integer());
            } else {
                sprite->set_z_order(0);
            }

            if (animation.has_value()) {
                animation->update();

                if (animation->done()) {
                    animation.reset();

                    // Getting pretty deeply nested here, could break this out into a method...
                    if (current_animation_generator.has_value()) {
                        animation = current_animation_generator.value()(*sprite);
                    }
                }
            }
        }
    }

    vec3 world_object::test_movement(sp::world_state& world_state, vec3 movement) {
        vec3 new_position = position + movement;

        bn::fixed_rect collider(bn::fixed_point(new_position.x, new_position.z), collider_size);
        for (bn::fixed_rect& world_collider : world_state.get_colliders()) {
            if (world_collider.touches(collider)) return vec3::zero;
        }

        return movement;
    }
}

