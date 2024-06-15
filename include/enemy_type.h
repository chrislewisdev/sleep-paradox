#pragma once

#include "bn_sprite_item.h"

#include "rpg.h"

namespace sp {
    class enemy_type {
        public:
            enemy_type(rpg_stats _stats, bn::sprite_item _sprite_item);

            static const enemy_type basic;

            rpg_stats stats;
            bn::sprite_item sprite_item;
    };
}
