#include "world_object_wall.h"

#include "world_state.h"
#include "world_camera.h"

#include "bn_sprite_items_wall_default.h"

namespace sp {
    world_object_wall::world_object_wall(vec3 _position, vec3 _facing) :
        world_object(bn::sprite_items::wall_default),
        facing(_facing)
    {
        position = _position;
    }

    world_object_wall::world_object_wall(vec3 _position, vec3 _facing, const bn::sprite_item& texture) :
        world_object(texture),
        facing(_facing)
    {
        position = _position;
    }

    void world_object_wall::update(sp::world_state& world_state) {
        world_camera& camera = world_state.get_camera();
        if (sprite.has_value()) {
            bool is_visible = facing.dot(camera.get_direction()) > 0;
            sprite->set_visible(is_visible);
            if (facing.z != 0) {
                sprite->set_affine_mat(camera.get_affine_transform_ptr_xy());
            } else {
                sprite->set_affine_mat(camera.get_affine_transform_ptr_yz());
            }
        }

        world_object::update(world_state);
    }
}
