#pragma once

#include "world_object.h"

namespace sp {
    class world_object_prop : public world_object {
        public:
            world_object_prop(vec3 p, const bn::sprite_item& _sprite) : world_object(_sprite) {
                position = p;
            }

            void update(sp::world_state& world_state) {
                world_object::update(world_state);
            }
    };
}

