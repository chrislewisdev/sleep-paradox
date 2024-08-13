#pragma once

#include "world_object.h"

namespace sp {
    class world_object_wall : public world_object {
        private:
            vec3 facing;

        public:
            world_object_wall(vec3 _position, vec3 _facing);
            world_object_wall(vec3 _position, vec3 _facing, const bn::sprite_item& texture);

            void update(sp::world_state& world_state);
    };
}
