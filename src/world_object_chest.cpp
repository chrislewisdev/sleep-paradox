#include "world_object_chest.h"

#include "world_state.h"

#include "bn_sprite_items_chest.h"

namespace sp {
    world_object_chest::world_object_chest(const vec3& _position) :
        world_object(bn::sprite_items::chest)
    {
        position = _position;
    }

    vec3 world_object_chest::get_position() const { return position; }
    void world_object_chest::interact(sp::world_state& world_state) const {}
}

