#include "enemy_type.h"

#include "bn_sprite_items_tooth.h"
#include "bn_sprite_items_cage.h"
#include "bn_sprite_items_creeper.h"
#include "bn_sprite_items_thrower.h"

namespace sp {
    enemy_type::enemy_type(rpg_stats _stats, const bn::sprite_item& _sprite_item)
        : stats(_stats), sprite_item(_sprite_item)
    {}

    const enemy_type enemy_type::tooth(
        rpg_stats(10, 5, 5, 2),
        bn::sprite_items::tooth
    );
    const enemy_type enemy_type::cage(
        rpg_stats(10, 5, 5, 2),
        bn::sprite_items::cage
    );
    const enemy_type enemy_type::creeper(
        rpg_stats(10, 5, 5, 2),
        bn::sprite_items::creeper
    );
    const enemy_type enemy_type::thrower(
        rpg_stats(10, 5, 5, 2),
        bn::sprite_items::thrower
    );
}
