#include "world_zone.h"

#include "bn_vector.h"
#include "bn_affine_bg_map_cell_info.h"

#include "bn_affine_bg_items_zone_sandbox_floor.h"
#include "bn_affine_bg_items_zone_sandbox_ceiling.h"
#include "bn_affine_bg_items_zone_uri_floor.h"
#include "bn_affine_bg_items_zone_uri_ceiling.h"
#include "bn_affine_bg_tiles_items_placeholder_tiles.h"

#include "sp_zone_sample_8x8.h"

namespace sp {
    constexpr int metatile_size = 32;
    constexpr int tile_size = 8;

    const bn::affine_bg_item sample_8x8_floor(bn::affine_bg_tiles_items::placeholder_tiles, bn::affine_bg_tiles_items::placeholder_tiles_palette, sp::zone_sample_8x8::floor_map);
    const bn::affine_bg_item sample_8x8_ceiling(bn::affine_bg_tiles_items::placeholder_tiles, bn::affine_bg_tiles_items::placeholder_tiles_palette, sp::zone_sample_8x8::ceiling_map);
    const world_zone world_zone::uri(
        sample_8x8_floor,
        sample_8x8_ceiling,
        vec3(sp::zone_sample_8x8::spawn_point_x(), 16, sp::zone_sample_8x8::spawn_point_y()),
        bn::span(sp::zone_sample_8x8::enemy_spawns)
    );

    world_zone::world_zone(
        const bn::affine_bg_item& _floor,
        const bn::affine_bg_item& _ceiling,
        vec3 _player_spawn,
        const bn::span<const enemy_spawn>& _enemy_spawns
    ) :
        floor(_floor),
        ceiling(_ceiling),
        player_spawn(_player_spawn),
        enemy_spawns(_enemy_spawns)
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

    vec3 world_zone::get_player_spawn() const { return player_spawn; }

    const bn::span<const enemy_spawn>& world_zone::get_enemy_spawns() const { return enemy_spawns; }

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
