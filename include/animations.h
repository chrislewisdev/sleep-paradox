#pragma once

#include "bn_sprite_animate_actions.h"

#include "world_object.h"

#include "bn_sprite_items_fred_sprite_sheet.h"

namespace sp::animations {
    namespace player {
        constexpr bn::sprite_tiles_item tiles = bn::sprite_items::fred_sprite_sheet.tiles_item();

        world_object_animation idle(const bn::sprite_ptr& sprite) {
            return bn::create_sprite_animate_action_forever(sprite, 30, tiles, 9, 10);
        }
        world_object_animation run(const bn::sprite_ptr& sprite) {
            return bn::create_sprite_animate_action_forever(sprite, 5, tiles, 0, 1, 2, 3, 4, 5);
        }
        world_object_animation blink(const bn::sprite_ptr sprite) {
            return bn::create_sprite_animate_action_once(sprite, 20, tiles, 7, 8);
        }
    }
}
