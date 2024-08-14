#include "wall_generator.h"

#include "bn_fixed_point.h"
#include "bn_fixed_size.h"

#include "bn_sprite_items_wall_default.h"
#include "bn_sprite_items_wall_alt01.h"
#include "bn_sprite_items_wall_alt02.h"
#include "bn_sprite_items_wall_alt03.h"
#include "bn_sprite_items_wall_exterior.h"

namespace sp {
    constexpr int empty_tile = 0;

    int get_zone_padding_left(const world_zone& zone) {
        for (int x = 0; x < zone.get_width(); x++) {
            for (int y = 0; y < zone.get_height(); y++) {
                if (zone.get_ceiling_tile(x, y) != empty_tile) return x;
            }
        }

        // Should only happen on an empty map...
        return zone.get_width();
    }
    int get_zone_padding_right(const world_zone& zone) {
        for (int x = zone.get_width() - 1; x >= 0; x--) {
            for (int y = 0; y < zone.get_height(); y++) {
                if (zone.get_ceiling_tile(x, y) != empty_tile) return zone.get_width() - 1 - x;
            }
        }

        // Should only happen on an empty map...
        return zone.get_width();
    }
    int get_zone_padding_top(const world_zone& zone) {
        for (int y = 0; y < zone.get_height(); y++) {
            for (int x = 0; x < zone.get_width(); x++) {
                if (zone.get_ceiling_tile(x, y) != empty_tile) return y;
            }
        }

        // Should only happen on an empty map...
        return zone.get_height();
    }
    int get_zone_padding_bottom(const world_zone& zone) {
        for (int y = zone.get_height() - 1; y >= 0; y--) {
            for (int x = 0; x < zone.get_width(); x++) {
                if (zone.get_ceiling_tile(x, y) != empty_tile) return zone.get_height() - 1 - y;
            }
        }

        // Should only happen on an empty map...
        return zone.get_height();
    }

    const bn::sprite_item& get_wall_texture(int tile_id) {
        switch (tile_id) {
            case 15: return bn::sprite_items::wall_alt01;
            case 31: return bn::sprite_items::wall_alt02;
            case 47: return bn::sprite_items::wall_alt03;
            case 65:
            case 80:
            case 83:
            case 113: return bn::sprite_items::wall_exterior;
            default: return bn::sprite_items::wall_default;
        }
    }

    void wall_generator::generate_walls(const world_zone& zone, bn::ivector<world_object_wall>& storage) {
        const int metatile_size = zone.get_metatile_size();
        const int half_width = (zone.get_width() / 2) * metatile_size;
        const int half_height = (zone.get_height() / 2) * metatile_size;

        for (int y = 0; y < zone.get_height(); y++) {
            for (int x = 0; x < zone.get_width(); x++) {
                int tile = zone.get_ceiling_tile(x, y);

                if (tile != empty_tile) {
                    int left = x - 1 >= 0 ? zone.get_ceiling_tile(x - 1, y) : 1;
                    int right = x + 1 < zone.get_width() ? zone.get_ceiling_tile(x + 1, y) : 1;
                    int up = y - 1 >= 0 ? zone.get_ceiling_tile(x, y - 1) : 1;
                    int down = y + 1 < zone.get_height() ? zone.get_ceiling_tile(x, y + 1) : 1;

                    vec3 wall_position(
                        x * metatile_size + (metatile_size / 2) - half_width,
                        metatile_size / 2,
                        half_height - y * metatile_size - (metatile_size / 2)
                    );

                    if (left == empty_tile) {
                        vec3 offset(-metatile_size / 2, 0, 0);
                        storage.push_back(world_object_wall(wall_position + offset, -vec3::right, get_wall_texture(zone.get_ceiling_tile_west(x, y))));
                    }
                    if (right == empty_tile) {
                        vec3 offset(metatile_size / 2, 0, 0);
                        storage.push_back(world_object_wall(wall_position + offset, vec3::right, get_wall_texture(zone.get_ceiling_tile_east(x, y))));
                    }
                    if (up == empty_tile) {
                        vec3 offset(0, 0, metatile_size / 2);
                        storage.push_back(world_object_wall(wall_position + offset, vec3::forward, get_wall_texture(zone.get_ceiling_tile_north(x, y))));
                    }
                    if (down == empty_tile) {
                        vec3 offset(0, 0, -metatile_size / 2);
                        storage.push_back(world_object_wall(wall_position + offset, -vec3::forward, get_wall_texture(zone.get_ceiling_tile_south(x, y))));
                    }
                }
            }
        }

        // Generate edge walls
        /*for (int x = 0; x < zone.get_width(); x++) {
            // Top edge
            if (zone.get_ceiling_tile(x, zone.get_height() - 1) == empty_tile)
                storage.push_back(world_object_wall(vec3(x * metatile_size + metatile_size / 2 - half_width, metatile_size / 2, -half_height), vec3::forward));
            // Bottom edge
            if (zone.get_ceiling_tile(x, 0) == empty_tile)
                storage.push_back(world_object_wall(vec3(x * metatile_size + metatile_size / 2 - half_width, metatile_size / 2, half_height), -vec3::forward));
        }
        for (int y = 0; y < zone.get_height(); y++) {
            // Left edge
            if (zone.get_ceiling_tile(0, y) == empty_tile)
                storage.push_back(world_object_wall(vec3(-half_width, metatile_size / 2, half_height - (y * metatile_size + metatile_size / 2)), vec3::right));
            // Right edge
            if (zone.get_ceiling_tile(zone.get_width() - 1, y) == empty_tile)
                storage.push_back(world_object_wall(vec3(half_width, metatile_size / 2, half_height - (y * metatile_size + metatile_size / 2)), -vec3::right));
        }*/
    }

    bool is_wall_contiguous(const world_zone& zone, int x, int y, int width) {
        for (int cursor_x = x; cursor_x < x + width; cursor_x++) {
            if (zone.get_ceiling_tile(cursor_x, y) == empty_tile) return false;
        }

        return true;
    }

    void wall_generator::generate_colliders(const world_zone& zone, bn::ivector<bn::fixed_rect>& storage) {
        const int metatile_size = zone.get_metatile_size();
        const int half_width = (zone.get_width() / 2) * metatile_size;
        const int half_height = (zone.get_height() / 2) * metatile_size;

        for (int y = 0; y < zone.get_height(); y++) {
            for (int x = 0; x < zone.get_width(); x++) {
                int tile = zone.get_ceiling_tile(x, y);

                if (tile != empty_tile) {
                    bn::fixed_point position(
                        x * metatile_size - half_width,
                        half_height - y * metatile_size - metatile_size
                    );

                    // Check if a collider already exists for this point on the map
                    bool is_covered = false;
                    for (bn::fixed_rect& collider : storage) {
                        if (collider.edge_contains(position)) {
                            is_covered = true;
                            break;
                        }
                    }
                    if (is_covered) continue;
                    
                    // Start generating a collider
                    int cursor_x = x + 1, cursor_y = y;
                    int width = 1, height = 1;
                    // Extend horizontally until we run out of wall tiles
                    while (cursor_x < zone.get_width() && zone.get_ceiling_tile(cursor_x, cursor_y) != empty_tile) {
                        width++;
                        cursor_x++;
                    }
                    // Extend vertically until the wall no longer conforms to a rectangular shape
                    cursor_x -= width;
                    cursor_y++;
                    while (cursor_y < zone.get_height() && is_wall_contiguous(zone, cursor_x, cursor_y, width)) {
                        height++;
                        cursor_y++;
                    }

                    // We ran out of contiguous wall space, register this collider
                    bn::fixed_size size(width * metatile_size, height * metatile_size);
                    bn::fixed_point centerpoint(
                        position.x() + size.width() / 2,
                        // The Y axis needs some correction because our co-ordinate space is kind of inverted from Butano's
                        // Our positive Z axis = Butano's negative Y axis
                        position.y() + size.height() / 2 - (height - 1) * metatile_size
                    );
                    storage.push_back(bn::fixed_rect(centerpoint, size));
                }
            }
        }

        // Generate edge colliders
        int padding_left = get_zone_padding_left(zone) * metatile_size;
        int padding_right = get_zone_padding_right(zone) * metatile_size;
        int padding_top = get_zone_padding_top(zone) * metatile_size;
        int padding_bottom = get_zone_padding_bottom(zone) * metatile_size;
        storage.push_back(bn::fixed_rect(bn::fixed_point(0, -half_height - metatile_size / 2 + padding_bottom), bn::fixed_size(half_width * 2, metatile_size)));
        storage.push_back(bn::fixed_rect(bn::fixed_point(0, half_height + metatile_size / 2 - padding_top), bn::fixed_size(half_width * 2, metatile_size)));
        storage.push_back(bn::fixed_rect(bn::fixed_point(-half_width - metatile_size / 2 + padding_left, 0), bn::fixed_size(metatile_size, half_height * 2)));
        storage.push_back(bn::fixed_rect(bn::fixed_point(half_width + metatile_size / 2 - padding_right, 0), bn::fixed_size(metatile_size, half_height * 2)));

    }
}
