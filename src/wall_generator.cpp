#include "wall_generator.h"

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
}
