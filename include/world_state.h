#pragma once

#include "bn_vector.h"
#include "bn_fixed_rect.h"

#include "world_zone.h"
#include "world_camera.h"
#include "world_object_player.h"
#include "world_object_wall.h"
#include "world_object_enemy.h"
#include "world_object_chest.h"
#include "world_object_projectile.h"
#include "world_object_prop.h"
#include "world_object_boss.h"
#include "fx_callout.h"

namespace sp {
    class world_state {
        private:
            const world_zone* current_zone;
            world_camera camera;
            world_object_player player;
            bn::vector<world_object_wall, 256> walls;
            bn::vector<world_object_enemy, 16> enemies;
            bn::vector<bn::fixed_rect, 32> colliders;
            bn::vector<fx_callout, 16> callouts;
            bn::vector<world_object_chest, 4> chests;
            bn::vector<world_object_projectile, 8> projectiles;
            bn::vector<world_object_prop, 8> props;
            bn::sprite_text_generator small_text_generator;
            bool is_visible;
            bn::optional<const portal*> queued_zone_change;
            bn::optional<world_object_boss> boss;

        public:
            world_state();

            const world_zone& get_current_zone() const;
            bool is_final_zone() const;
            world_camera& get_camera();
            world_object_player& get_player();
            bn::ivector<world_object_wall>& get_walls();
            bn::ivector<world_object_enemy>& get_enemies();
            bn::ivector<world_object_chest>& get_chests();
            bn::ivector<bn::fixed_rect>& get_colliders();
            bn::optional<world_object_boss>& get_boss();
            bool get_visible() const;
            void set_visible(bool visible);

            void update();
            void load_zone(const world_zone& zone);
            void create_damage_callout(bn::fixed_point position, int amount, bool is_weak);
            void create_callout(bn::fixed_point position, const bn::string_view& text);
            void queue_zone_change(const portal& portal);
            bool is_zone_change_queued() const;
            void process_zone_change();
            void respawn();
            void cleanup();

            void activate_chest(const world_object_chest& chest);
            void spawn_projectile(world_object_projectile&& projectile);
    };
}
