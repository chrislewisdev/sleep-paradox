#include "world_object_projectile.h"

#include "world_state.h"
#include "animations.h"

#include "bn_sprite_items_apple_sheet.h"

namespace sp {
    world_object_projectile::world_object_projectile(vec3 _position, vec3 _velocity) :
        world_object(bn::sprite_items::apple_sheet),
        velocity(_velocity)
    {
        position = _position;

        active = true;

        use_animation("spin", sp::animations::apple::spin);
    }

    bool world_object_projectile::is_active() const { return active; }

    void world_object_projectile::update(sp::world_state& world_state) {
        position = position + velocity;

        // TODO: Check for player collision!

        for (auto& collider : world_state.get_colliders()) {
            if (collider.touches(get_collider())) {
                active = false;
            }
        }

        world_object::update(world_state);
    }
}

