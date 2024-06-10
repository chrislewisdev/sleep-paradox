#include "world_object.h"

#include "world_state.h"
#include "world_camera.h"

namespace sp {
    world_object::world_object(const bn::sprite_item& _sprite_item)
        : position(0, 16, 0),
          sprite_item(_sprite_item)
    {
        sprite = sprite_item.create_sprite(0, 0);
        sprite->set_bg_priority(2);
    }

    const vec3& world_object::get_position() const {
        return position;
    }

    void world_object::set_position(const vec3& _position) {
        position = _position;
    }

    void world_object::use_animation(const bn::string_view& name, bn::sprite_animate_action<10> (*generator)(const bn::sprite_ptr&)) {
        if (current_animation_name == name) return;

        current_animation_name = name;
        animation = generator(*sprite);
    }

    void world_object::update(sp::world_state& world_state) {
        world_camera& camera = world_state.get_camera();
        bn::fixed scale = camera.get_scale();
        // Translation was supposed to be part of the world transform but that was broken so we just do it manually :(
        vec3 screen_position = (position - camera.get_position()) * camera.get_world_transform() * scale;

        // TODO: Check if sprite is on/off screen, update sprite accordingly

        if (sprite.has_value()) {
            sprite->set_position(screen_position.x, screen_position.z);
            // This currently requires that we increase the sort layers in the Makefile
            // We can optimise more by not creating sprites for walls that aren't visible at all
            sprite->set_z_order(-screen_position.z.integer());
        }

        if (animation.has_value()) {
            animation->update();
        }
    }
}

