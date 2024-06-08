#pragma once

#include "bn_affine_bg_item.h"

namespace sp {
    class world_zone {
        public:
            const bn::affine_bg_item& floor;
            const bn::affine_bg_item& ceiling;

            static const world_zone sandbox;

            world_zone(const bn::affine_bg_item& _floor, const bn::affine_bg_item& _ceiling);
    };
}
