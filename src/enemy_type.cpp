#include "enemy_type.h"
#include "animations.h"

#include "bn_sprite_items_tooth.h"
#include "bn_sprite_items_cage.h"
#include "bn_sprite_items_creeper.h"
#include "bn_sprite_items_thrower.h"

namespace sp {
    enemy_type::enemy_type(
        rpg_stats _stats,
        int _xp_reward,
        sp::behaviour_type _behaviour_type,
        const bn::sprite_item& _sprite_item,
        bn::optional<animation_generator> _move_animation,
        bn::optional<animation_generator> _attack_animation,
        bn::optional<animation_generator> _attack_loop_animation,
        bn::optional<animation_generator> _attack_end_animation
    ) : 
        stats(_stats),
        xp_reward(_xp_reward),
        behaviour_type(_behaviour_type),
        sprite_item(_sprite_item),
        move_animation(_move_animation),
        attack_animation(_attack_animation),
        attack_loop_animation(_attack_loop_animation),
        attack_end_animation(_attack_end_animation)
    {}

    const enemy_type enemy_type::tooth(
        rpg_stats(12, 8, 5, 2),
        7,
        behaviour_type::charger,
        bn::sprite_items::tooth,
        sp::animations::tooth::move,
        sp::animations::tooth::windup,
        sp::animations::tooth::charge,
        sp::animations::tooth::bonk
    );
    const enemy_type enemy_type::cage(
        rpg_stats(20, 6, 2, 2),
        10,
        behaviour_type::trapper,
        bn::sprite_items::cage,
        sp::animations::cage::move,
        sp::animations::cage::attack,
        sp::animations::cage::trapped,
        sp::animations::cage::release
    );
    const enemy_type enemy_type::creeper(
        rpg_stats(8, 3, 1, 2),
        4,
        behaviour_type::melee,
        bn::sprite_items::creeper,
        sp::animations::creeper::move,
        sp::animations::creeper::attack,
        bn::nullopt,
        bn::nullopt

    );
    const enemy_type enemy_type::thrower(
        rpg_stats(10, 5, 3, 2),
        6,
        behaviour_type::ranged,
        bn::sprite_items::thrower,
        sp::animations::thrower::move,
        sp::animations::thrower::attack,
        bn::nullopt,
        bn::nullopt
    );
}
