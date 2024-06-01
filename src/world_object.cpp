#include "world_object.h"

namespace sp {
    world_object::world_object(const bn::sprite_item& _sprite_item)
        : sprite_item(_sprite_item)
    {
        sprite = sprite_item.create_sprite(0, 0);
        sprite->set_bg_priority(2);
        position = vec3(50, 8, 50);
    }

    const vec3& world_object::get_position() const {
        return position;
    }

    void world_object::set_position(const vec3& _position) {
        position = _position;
    }

    void world_object::update(const world_camera& camera) {
        bn::fixed scale = camera.get_scale();
        vec3 screen_position = position * camera.get_world_transform() * scale;

        // TODO: Check if sprite is on/off screen, update sprite accordingly

        if (sprite.has_value()) {
            sprite->set_position(screen_position.x, screen_position.z);
        }
    }
}

