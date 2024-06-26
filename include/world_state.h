#pragma once

#include "bn_vector.h"
#include "bn_fixed_rect.h"

#include "world_zone.h"
#include "world_camera.h"
#include "world_object_player.h"
#include "world_object_wall.h"
#include "world_object_enemy.h"
#include "fx_damage_callout.h"

namespace sp {
    class world_state {
        private:
            const world_zone* current_zone;
            world_camera camera;
            world_object_player player;
            bn::vector<world_object_wall, 128> walls;
            bn::vector<world_object_enemy, 16> enemies;
            bn::vector<bn::fixed_rect, 32> colliders;
            bn::vector<fx_damage_callout, 16> damage_callouts;
            bn::sprite_text_generator small_text_generator;

        public:
            world_state();

            const world_zone& get_current_zone() const;
            world_camera& get_camera();
            world_object_player& get_player();
            bn::ivector<world_object_wall>& get_walls();
            bn::ivector<world_object_enemy>& get_enemies();
            bn::ivector<bn::fixed_rect>& get_colliders();

            void update();
            void load_zone(const world_zone& zone);
            void create_damage_callout(bn::fixed_point position, int amount, bool is_weak);
    };
}
