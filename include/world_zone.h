#pragma once

#include "bn_affine_bg_item.h"

namespace sp {
    class world_zone {
        public:
            const bn::affine_bg_item& floor;
            const bn::affine_bg_item& ceiling;

            static const world_zone sandbox;

            world_zone(const bn::affine_bg_item& _floor, const bn::affine_bg_item& _ceiling);

            int get_metatile_size() const;

            int get_width() const;
            int get_height() const;

            int get_ceiling_tile(int x, int y) const;
    };
}
