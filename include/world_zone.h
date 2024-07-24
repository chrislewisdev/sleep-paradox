#pragma once

#include "bn_span.h"
#include "bn_affine_bg_item.h"

#include "vec3.h"
#include "sp_enemy_spawn.h"
#include "portal.h"

namespace sp {
    class world_zone {
        public:
            const bn::affine_bg_item& floor;
            const bn::affine_bg_item& ceiling;
            vec3 player_spawn;
            const bn::span<const enemy_spawn> enemy_spawns;
            const bn::span<const portal> portals;

            static const world_zone sample_8x8;
            static const world_zone alternate;

            world_zone(
                const bn::affine_bg_item& _floor,
                const bn::affine_bg_item& _ceiling,
                vec3 _player_spawn,
                const bn::span<const enemy_spawn>& _enemy_spawns,
                const bn::span<const portal>& _portals
            );

            int get_metatile_size() const;

            int get_width() const;
            int get_height() const;

            vec3 get_player_spawn() const;

            const bn::span<const enemy_spawn>& get_enemy_spawns() const;
            const bn::span<const portal>& get_portals() const;

            int get_ceiling_tile(int x, int y) const;
            int get_ceiling_tile(vec3 position) const;

    };
}
