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
    }

    bool world_object_projectile::is_active() const { return active; }

    void world_object_projectile::update(sp::world_state& world_state) {
        use_animation("spin", sp::animations::apple::spin);

        position = position + velocity;

        auto collider = bn::fixed_rect(position.to_point(), bn::fixed_size(4, 4));
        auto& player = world_state.get_player();
        if (player.get_collider().touches(collider)) {
            player.receive_attack(world_state, enemy_type::thrower.stats);
            active = false;
        }

        for (auto& world_collider : world_state.get_colliders()) {
            if (collider.touches(world_collider)) {
                active = false;
            }
        }

        world_object::update(world_state);
    }
}

