#include "enemy_type.h"

#include "bn_sprite_items_bully01_side_profile.h"

namespace sp {
    enemy_type::enemy_type(rpg_stats _stats, bn::sprite_item _sprite_item)
        : stats(_stats), sprite_item(_sprite_item)
    {}

    const enemy_type enemy_type::basic(
        rpg_stats(10, 5, 5, 2),
        bn::sprite_items::bully01_side_profile
    );
}
