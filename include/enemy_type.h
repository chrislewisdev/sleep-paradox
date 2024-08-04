#pragma once

#include "bn_sprite_item.h"
#include "bn_optional.h"

#include "rpg.h"
#include "world_object.h"

namespace sp {
    class enemy_type {
        public:
            enemy_type(rpg_stats _stats, int _xp_reward, const bn::sprite_item& _sprite_item, bn::optional<animation_generator> _move_animation);

            static const enemy_type tooth;
            static const enemy_type cage;
            static const enemy_type creeper;
            static const enemy_type thrower;

            rpg_stats stats;
            int xp_reward;
            const bn::sprite_item& sprite_item;
            bn::optional<animation_generator> move_animation;
    };
}
