#pragma once

#include "bn_sprite_animate_actions.h"

#include "world_object.h"

#include "bn_sprite_items_fred_sprite_sheet.h"
#include "bn_sprite_items_attack_fx.h"
#include "bn_sprite_items_cage_sheet.h"
#include "bn_sprite_items_tooth_sheet.h"
#include "bn_sprite_items_creeper_sheet.h"
#include "bn_sprite_items_thrower_sheet.h"
#include "bn_sprite_items_apple_sheet.h"

namespace sp::animations {
    namespace player {
        constexpr bn::sprite_tiles_item tiles = bn::sprite_items::fred_sprite_sheet.tiles_item();

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
            return bn::create_sprite_animate_action_once(sprite, 5, tiles, 13, 14, 9);
        }
    }
    namespace attack_fx {
        constexpr bn::sprite_tiles_item tiles = bn::sprite_items::attack_fx.tiles_item();

        inline world_object_animation punch(const bn::sprite_ptr& sprite) {
            return bn::create_sprite_animate_action_once(sprite, 5, tiles, 2, 3, 2);
        }
    }
    
    namespace creeper {
        constexpr bn::sprite_tiles_item tiles = bn::sprite_items::creeper_sheet.tiles_item();

        inline world_object_animation move(const bn::sprite_ptr& sprite) {
            return bn::create_sprite_animate_action_forever(sprite, 5, tiles, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
        }
    }
    namespace cage {
        constexpr bn::sprite_tiles_item tiles = bn::sprite_items::cage_sheet.tiles_item();

        inline world_object_animation move(const bn::sprite_ptr& sprite) {
            return bn::create_sprite_animate_action_forever(sprite, 5, tiles, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
        }
    }
    namespace tooth {
        constexpr bn::sprite_tiles_item tiles = bn::sprite_items::tooth_sheet.tiles_item();

        inline world_object_animation move(const bn::sprite_ptr& sprite) {
            return bn::create_sprite_animate_action_forever(sprite, 5, tiles, 0, 1, 2, 3, 4, 5, 6, 7);
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
            return bn::create_sprite_animate_action_forever(sprite, 5, tiles, 0, 1, 2, 3, 4, 5, 6, 7);
        }
    }
}
