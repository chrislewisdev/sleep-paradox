#include "world_zone.h"

#include "bn_affine_bg_items_zone_sandbox_floor.h"
#include "bn_affine_bg_items_zone_sandbox_ceiling.h"

namespace sp {
    const world_zone world_zone::sandbox(bn::affine_bg_items::zone_sandbox_floor, bn::affine_bg_items::zone_sandbox_ceiling);

    world_zone::world_zone(const bn::affine_bg_item& _floor, const bn::affine_bg_item& _ceiling) :
        floor(_floor),
        ceiling(_ceiling)
    {}
}
