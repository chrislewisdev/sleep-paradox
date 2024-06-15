#include "wall_generator.h"

#include "bn_fixed_point.h"
#include "bn_fixed_size.h"

namespace sp {
    void wall_generator::generate_walls(const world_zone& zone, bn::ivector<world_object_wall>& storage) {
        const int metatile_size = zone.get_metatile_size();
        const int half_width = (zone.get_width() / 2) * metatile_size;
        const int half_height = (zone.get_height() / 2) * metatile_size;

        for (int y = 0; y < zone.get_height(); y++) {
            for (int x = 0; x < zone.get_width(); x++) {
                int tile = zone.get_ceiling_tile(x, y);

                if (tile != 0) {
                    int left = zone.get_ceiling_tile(x - 1, y);
                    int right = zone.get_ceiling_tile(x + 1, y);
                    int up = zone.get_ceiling_tile(x, y - 1);
                    int down = zone.get_ceiling_tile(x, y + 1);

                    vec3 wall_position(
                        x * metatile_size + (metatile_size / 2) - half_width,
                        metatile_size / 2,
                        half_height - y * metatile_size - (metatile_size / 2)
                    );

                    if (left == 0) {
                        vec3 offset(-metatile_size / 2, 0, 0);
                        storage.push_back(world_object_wall(wall_position + offset, -vec3::right));
                    }
                    if (right == 0) {
                        vec3 offset(metatile_size / 2, 0, 0);
                        storage.push_back(world_object_wall(wall_position + offset, vec3::right));
                    }
                    if (up == 0) {
                        vec3 offset(0, 0, metatile_size / 2);
                        storage.push_back(world_object_wall(wall_position + offset, vec3::forward));
                    }
                    if (down == 0) {
                        vec3 offset(0, 0, -metatile_size / 2);
                        storage.push_back(world_object_wall(wall_position + offset, -vec3::forward));
                    }
                }
            }
        }
    }

    bool is_wall_contiguous(const world_zone& zone, int x, int y, int width) {
        for (int cursor_x = x; cursor_x < x + width; cursor_x++) {
            if (zone.get_ceiling_tile(cursor_x, y) == 0) return false;
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

                if (tile != 0) {
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
                    while (zone.get_ceiling_tile(cursor_x, cursor_y) != 0) {
                        width++;
                        cursor_x++;
                    }
                    // Extend vertically until the wall no longer conforms to a rectangular shape
                    cursor_x -= width;
                    cursor_y++;
                    while (is_wall_contiguous(zone, cursor_x, cursor_y, width)) {
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
    }
}
