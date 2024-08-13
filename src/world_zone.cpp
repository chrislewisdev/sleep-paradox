#include "world_zone.h"

#include "bn_vector.h"
#include "bn_affine_bg_map_cell_info.h"

namespace sp {
    constexpr int metatile_size = 32;
    constexpr int tile_size = 8;

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
    const bn::span<const portal>& world_zone::get_portals() const { return portals; }

    int world_zone::get_ceiling_tile(int x, int y) const {
        int tx = x * (metatile_size / tile_size);
        int ty = y * (metatile_size / tile_size);

        auto cell = ceiling.map_item().cell(tx, ty);
        bn::affine_bg_map_cell_info cell_info(cell);
        
        // This is the 'tile' index NOT the 'metatile' index. Might need to change this later on
        return cell_info.tile_index();
    }

    int world_zone::get_ceiling_tile_north(int x, int y) const {
        int tx = x * (metatile_size / tile_size) + 1;
        int ty = y * (metatile_size / tile_size);

        auto cell = ceiling.map_item().cell(tx, ty);
        bn::affine_bg_map_cell_info cell_info(cell);
        
        return cell_info.tile_index();
    }
    int world_zone::get_ceiling_tile_south(int x, int y) const {
        int tx = x * (metatile_size / tile_size) + 1;
        int ty = y * (metatile_size / tile_size) + 3;

        auto cell = ceiling.map_item().cell(tx, ty);
        bn::affine_bg_map_cell_info cell_info(cell);
        
        return cell_info.tile_index();
    }
    int world_zone::get_ceiling_tile_west(int x, int y) const {
        int tx = x * (metatile_size / tile_size);
        int ty = y * (metatile_size / tile_size) + 1;

        auto cell = ceiling.map_item().cell(tx, ty);
        bn::affine_bg_map_cell_info cell_info(cell);
        
        return cell_info.tile_index();
    }
    int world_zone::get_ceiling_tile_east(int x, int y) const {
        int tx = x * (metatile_size / tile_size) + 3;
        int ty = y * (metatile_size / tile_size) + 1;

        auto cell = ceiling.map_item().cell(tx, ty);
        bn::affine_bg_map_cell_info cell_info(cell);
        
        return cell_info.tile_index();
    }

    int world_zone::get_ceiling_tile(vec3 position) const {
        int x = (position.x.integer() + floor.map_item().dimensions().width() * tile_size / 2) / metatile_size;
        int y = (floor.map_item().dimensions().height() * tile_size / 2 - position.z.integer()) / metatile_size;
        return get_ceiling_tile(x, y);
    }
}
