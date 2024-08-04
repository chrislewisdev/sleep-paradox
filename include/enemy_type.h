#pragma once

#include "bn_sprite_item.h"
#include "bn_optional.h"

#include "rpg.h"
#include "world_object.h"

namespace sp {
    enum class behaviour_type {
        melee,
        ranged,
    };

    class enemy_type {
        public:
            enemy_type(
                rpg_stats _stats,
                int _xp_reward,
                sp::behaviour_type _behaviour_type,
                const bn::sprite_item& _sprite_item,
                bn::optional<animation_generator> _move_animation,
                bn::optional<animation_generator> _attack_animation
            );

            static const enemy_type tooth;
            static const enemy_type cage;
            static const enemy_type creeper;
            static const enemy_type thrower;

            rpg_stats stats;
            int xp_reward;
            sp::behaviour_type behaviour_type;
            const bn::sprite_item& sprite_item;
            bn::optional<animation_generator> move_animation;
            bn::optional<animation_generator> attack_animation;
    };
}
