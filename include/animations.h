#pragma once

#include "bn_sprite_animate_actions.h"

#include "world_object.h"

#include "bn_sprite_items_fred_sprite_sheet.h"
#include "bn_sprite_items_fred_dash_sheet.h"
#include "bn_sprite_items_attack_fx.h"
#include "bn_sprite_items_cage_sheet.h"
#include "bn_sprite_items_cage_attack_sheet.h"
#include "bn_sprite_items_cage_trapped_sheet.h"
#include "bn_sprite_items_tooth_sheet.h"
#include "bn_sprite_items_tooth_windup_sheet.h"
#include "bn_sprite_items_tooth_charge_sheet.h"
#include "bn_sprite_items_tooth_hit_sheet.h"
#include "bn_sprite_items_creeper_sheet.h"
#include "bn_sprite_items_creeper_attack_sheet.h"
#include "bn_sprite_items_thrower_sheet.h"
#include "bn_sprite_items_apple_sheet.h"
#include "bn_sprite_items_boss_sheet.h"
#include "bn_sprite_items_boss_ball_sheet.h"

namespace sp::animations {
    namespace player {
        constexpr bn::sprite_tiles_item tiles = bn::sprite_items::fred_sprite_sheet.tiles_item();
        constexpr bn::sprite_tiles_item dash_tiles = bn::sprite_items::fred_dash_sheet.tiles_item();

        inline world_object_animation idle(const bn::sprite_ptr& sprite) {
            return bn::create_sprite_animate_action_forever(sprite, 30, tiles, 9, 10);
        }
        inline world_object_animation run(const bn::sprite_ptr& sprite) {
            return bn::create_sprite_animate_action_forever(sprite, 5, tiles, 0, 1, 2, 3, 4, 5);
        }
        inline world_object_animation blink(const bn::sprite_ptr sprite) {
            return bn::create_sprite_animate_action_once(sprite, 20, tiles, 7, 8);
        }
        inline world_object_animation punch(const bn::sprite_ptr& sprite) {
            return bn::create_sprite_animate_action_once(sprite, 5, tiles, 11, 12, 13, 14, 15, 11);
        }
        inline world_object_animation dash(const bn::sprite_ptr& sprite) {
            return bn::create_sprite_animate_action_once(sprite, 5, dash_tiles, 0, 1, 2, 0);
        }
    }
    namespace attack_fx {
        constexpr bn::sprite_tiles_item tiles = bn::sprite_items::attack_fx.tiles_item();

        inline world_object_animation punch(const bn::sprite_ptr& sprite) {
            return bn::create_sprite_animate_action_once(sprite, 5, tiles, 0, 1, 2, 3, 4, 4); 
        }
    }
    
    namespace creeper {
        constexpr bn::sprite_tiles_item tiles = bn::sprite_items::creeper_sheet.tiles_item();
        constexpr bn::sprite_tiles_item attack_tiles = bn::sprite_items::creeper_attack_sheet.tiles_item();

        inline world_object_animation move(const bn::sprite_ptr& sprite) {
            return bn::create_sprite_animate_action_forever(sprite, 5, tiles, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
        }
        inline world_object_animation attack(const bn::sprite_ptr& sprite) {
            return bn::create_sprite_animate_action_once(sprite, 5, attack_tiles, 0, 1, 2, 3, 4, 5, 6, 0);
        }
    }
    namespace cage {
        constexpr bn::sprite_tiles_item tiles = bn::sprite_items::cage_sheet.tiles_item();
        constexpr bn::sprite_tiles_item attack_tiles = bn::sprite_items::cage_attack_sheet.tiles_item();
        constexpr bn::sprite_tiles_item trapped_tiles = bn::sprite_items::cage_trapped_sheet.tiles_item();

        inline world_object_animation move(const bn::sprite_ptr& sprite) {
            return bn::create_sprite_animate_action_forever(sprite, 5, tiles, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
        }
        inline world_object_animation attack(const bn::sprite_ptr& sprite) {
            return bn::create_sprite_animate_action_once(sprite, 5, attack_tiles, 0, 1, 2, 3, 4, 5, 0);
        }
        inline world_object_animation trapped(const bn::sprite_ptr& sprite) {
            return bn::create_sprite_animate_action_forever(sprite, 5, trapped_tiles, 0, 1, 2, 3, 4, 5);
        }
        inline world_object_animation release(const bn::sprite_ptr& sprite) {
            return bn::create_sprite_animate_action_once(sprite, 2, attack_tiles, 1, 2, 3, 4, 0);
        }
    }
    namespace tooth {
        constexpr bn::sprite_tiles_item tiles = bn::sprite_items::tooth_sheet.tiles_item();
        constexpr bn::sprite_tiles_item windup_tiles = bn::sprite_items::tooth_windup_sheet.tiles_item();
        constexpr bn::sprite_tiles_item charge_tiles = bn::sprite_items::tooth_charge_sheet.tiles_item();
        constexpr bn::sprite_tiles_item bonk_tiles = bn::sprite_items::tooth_hit_sheet.tiles_item();

        inline world_object_animation idle(const bn::sprite_ptr& sprite) {
            return bn::create_sprite_animate_action_forever(sprite, 5, tiles, 0, 0);
        }
        inline world_object_animation move(const bn::sprite_ptr& sprite) {
            return bn::create_sprite_animate_action_forever(sprite, 5, tiles, 0, 1, 2, 3, 4, 5, 6, 7);
        }
        inline world_object_animation windup(const bn::sprite_ptr& sprite) {
            return bn::create_sprite_animate_action_once(sprite, 5, windup_tiles, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
        }
        inline world_object_animation charge(const bn::sprite_ptr& sprite) {
            return bn::create_sprite_animate_action_forever(sprite, 5, charge_tiles, 0, 1, 2, 3, 4, 5, 6);
        }
        inline world_object_animation bonk(const bn::sprite_ptr& sprite) {
            return bn::create_sprite_animate_action_once(sprite, 5, bonk_tiles, 0, 1, 2, 3, 4);
        }
    }
    namespace thrower {
        constexpr bn::sprite_tiles_item tiles = bn::sprite_items::thrower_sheet.tiles_item();

        inline world_object_animation move(const bn::sprite_ptr& sprite) {
            return bn::create_sprite_animate_action_forever(sprite, 5, tiles, 0, 1, 2, 3, 4);
        }

        inline world_object_animation attack(const bn::sprite_ptr& sprite) {
            return bn::create_sprite_animate_action_once(sprite, 5, tiles, 5, 6, 7, 0);
        }
    }
    namespace apple {
        constexpr bn::sprite_tiles_item tiles = bn::sprite_items::apple_sheet.tiles_item();

        inline world_object_animation spin(const bn::sprite_ptr& sprite) {
            return bn::create_sprite_animate_action_forever(sprite, 1, tiles, 0, 1, 2, 3, 4, 5, 6, 7);
        }
    }

    namespace boss {
        constexpr bn::sprite_tiles_item tiles = bn::sprite_items::boss_sheet.tiles_item();
        constexpr bn::sprite_tiles_item ball_tiles = bn::sprite_items::boss_ball_sheet.tiles_item();

        inline world_object_animation idle(const bn::sprite_ptr& sprite) {
            return bn::create_sprite_animate_action_forever(sprite, 5, tiles, 12, 13, 14);
        }
        inline world_object_animation move(const bn::sprite_ptr& sprite) {
            return bn::create_sprite_animate_action_forever(sprite, 5, tiles, 31, 32, 33,34, 35, 36, 37);
        }
        inline world_object_animation attack(const bn::sprite_ptr& sprite) {
            return bn::create_sprite_animate_action_once(sprite, 5, tiles, 15, 16, 17, 18, 19, 20, 21, 22);
        }
        inline world_object_animation windup(const bn::sprite_ptr& sprite) {
            return bn::create_sprite_animate_action_once(sprite, 5, tiles, 23, 24, 25, 26, 27);
        }
        inline world_object_animation throw_attack(const bn::sprite_ptr& sprite) {
            return bn::create_sprite_animate_action_once(sprite, 5, tiles, 28, 29, 30, 30);
        }
        inline world_object_animation transform(const bn::sprite_ptr& sprite) {
            return bn::create_sprite_animate_action_once(sprite, 10, tiles, 4, 5, 6, 7, 8, 9, 10, 11, 11);
        }
        inline world_object_animation idle_human(const bn::sprite_ptr& sprite) {
            return bn::create_sprite_animate_action_forever(sprite, 5, tiles, 0, 1, 2, 3);
        }
        inline world_object_animation ball_spin(const bn::sprite_ptr& sprite) {
            return bn::create_sprite_animate_action_forever(sprite, 2, ball_tiles, 0, 1, 2, 3);
        }
    }
}
