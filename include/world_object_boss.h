#pragma once

#include "bn_random.h"

#include "world_object.h"
#include "rpg.h"
#include "world_object_enemy.h"

namespace sp {
    // Shamelessly copied and hacked together from enemy behaviours
    class world_object_boss : public world_object {
        private:
            void update_idle(sp::world_state& world_state);
            void update_chase(sp::world_state& world_state);
            void enter_attack();
            void update_attack(sp::world_state& world_state);

            int get_windup_duration() const;
            int get_attack_distance_squared() const;
            int get_attack_cooldown() const;

            rpg_stats stats;
            int health;

            enemy_state state = enemy_state::idle;
            int attack_windup;
            bn::random rng;
            bool use_melee;

        public:
            world_object_boss(vec3 position);

            const rpg_stats& get_stats() const;
            int get_health() const;
            int get_xp_reward() const;
            bool is_active() const;

            void update(sp::world_state& world_state);
            void receive_attack(sp::world_state& world_state, const rpg_stats& attacker);
    };
}
