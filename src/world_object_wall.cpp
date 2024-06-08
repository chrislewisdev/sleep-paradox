#include "world_object_wall.h"

#include "bn_sprite_items_wall_placeholder.h"

namespace sp {
    world_object_wall::world_object_wall(vec3 _position, vec3 _facing) :
        world_object(bn::sprite_items::wall_placeholder),
        facing(_facing)
    {
        position = _position;
    }

    void world_object_wall::update(const world_camera& camera) {
        world_object::update(camera);
    }
}
