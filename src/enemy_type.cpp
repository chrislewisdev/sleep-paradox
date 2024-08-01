#include "enemy_type.h"
#include "animations.h"

#include "bn_sprite_items_tooth.h"
#include "bn_sprite_items_cage.h"
#include "bn_sprite_items_creeper.h"
#include "bn_sprite_items_thrower.h"

namespace sp {
    enemy_type::enemy_type(rpg_stats _stats, int _xp_reward, const bn::sprite_item& _sprite_item, bn::optional<animation_generator> _move_animation)
        : stats(_stats), xp_reward(_xp_reward), sprite_item(_sprite_item), move_animation(_move_animation)
    {}

    const enemy_type enemy_type::tooth(
        rpg_stats(12, 8, 5, 2),
        7,
        bn::sprite_items::tooth,
        sp::animations::tooth::move
    );
    const enemy_type enemy_type::cage(
        rpg_stats(20, 6, 2, 2),
        10,
        bn::sprite_items::cage,
        sp::animations::cage::move
    );
    const enemy_type enemy_type::creeper(
        rpg_stats(8, 3, 1, 2),
        4,
        bn::sprite_items::creeper,
        sp::animations::creeper::move
    );
    const enemy_type enemy_type::thrower(
        rpg_stats(10, 5, 3, 2),
        6,
        bn::sprite_items::thrower,
        bn::nullopt
    );
}
