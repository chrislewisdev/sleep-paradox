#include "world_zone.h"

#include "bn_affine_bg_map_cell_info.h"

#include "bn_affine_bg_items_zone_sandbox_floor.h"
#include "bn_affine_bg_items_zone_sandbox_ceiling.h"
#include "bn_affine_bg_items_zone_uri_floor.h"
#include "bn_affine_bg_items_zone_uri_ceiling.h"

namespace sp {
    constexpr int metatile_size = 32;
    constexpr int tile_size = 8;

    const world_zone world_zone::sandbox(bn::affine_bg_items::zone_sandbox_floor, bn::affine_bg_items::zone_sandbox_ceiling);
    const world_zone world_zone::uri(bn::affine_bg_items::zone_uri_floor, bn::affine_bg_items::zone_uri_ceiling);

    world_zone::world_zone(const bn::affine_bg_item& _floor, const bn::affine_bg_item& _ceiling) :
        floor(_floor),
        ceiling(_ceiling)
    {}

    int world_zone::get_metatile_size() const {
        return metatile_size;
    }

    int world_zone::get_width() const {
        return floor.map_item().dimensions().width() / (metatile_size / tile_size);
    }

    int world_zone::get_height() const {
        return floor.map_item().dimensions().height() / (metatile_size / tile_size);
    }

    int world_zone::get_ceiling_tile(int x, int y) const {
        int tx = x * (metatile_size / tile_size);
        int ty = y * (metatile_size / tile_size);

        auto cell = ceiling.map_item().cell(tx, ty);
        bn::affine_bg_map_cell_info cell_info(cell);
        
        // This is the 'tile' index NOT the 'metatile' index. Might need to change this later on
        return cell_info.tile_index();
    }

    int world_zone::get_ceiling_tile(vec3 position) const {
        int x = (position.x.integer() + floor.map_item().dimensions().width() * tile_size / 2) / metatile_size;
        int y = (floor.map_item().dimensions().height() * tile_size / 2 - position.z.integer()) / metatile_size;
        return get_ceiling_tile(x, y);
    }
}
