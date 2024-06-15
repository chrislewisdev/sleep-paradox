#pragma once

#include "bn_vector.h"
#include "bn_fixed_rect.h"

#include "world_zone.h"
#include "world_object_wall.h"

namespace sp {
    class wall_generator {
        public:
            void generate_walls(const world_zone& zone, bn::ivector<world_object_wall>& storage);
            void generate_colliders(const world_zone& zone, bn::ivector<bn::fixed_rect>& storage);
    };
}
