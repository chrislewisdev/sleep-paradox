#include "world_object.h"

#include "bn_display.h"

#include "world_state.h"
#include "world_camera.h"

namespace sp {
    world_object::world_object(const bn::sprite_item& _sprite_item)
        : position(0, 16, 0),
          sprite_item(_sprite_item)
    {
    }

    const vec3& world_object::get_position() const {
        return position;
    }

    void world_object::set_position(const vec3& _position) {
        position = _position;
    }

    void world_object::use_animation(const bn::string_view& name, animation_generator generator) {
        if (!sprite.has_value() || current_animation_name == name) return;

        current_animation_name = name;
        animation = generator(*sprite);
    }

    void world_object::update(sp::world_state& world_state) {
        world_camera& camera = world_state.get_camera();
        bn::fixed scale = camera.get_scale();
        // Translation was supposed to be part of the world transform but that was broken so we just do it manually :(
        vec3 screen_position = (position - camera.get_position()) * camera.get_world_transform() * scale;

        // Check if sprite is on/off screen
        constexpr int clip_left = -bn::display::width() / 2 - 32;
        constexpr int clip_right = bn::display::width() / 2 + 32;
        constexpr int clip_top = bn::display::height() / 2 + 32;
        constexpr int clip_bottom = -bn::display::height() / 2 - 32;
        const bool visible = !(screen_position.x < clip_left || screen_position.x > clip_right || screen_position.z < clip_bottom || screen_position.z > clip_top);

        // Butano already filters out off-screen sprites, but by using less sprite_ptrs we save on sorting layers
        if (!visible && sprite.has_value()) {
            if (animation.has_value()) {
                animation.reset();
            }
            sprite.reset();
        } else if (visible && !sprite.has_value()) {
            sprite = sprite_item.create_sprite(0, 0);
            sprite->set_bg_priority(2);
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
            }
        }
    }
}

