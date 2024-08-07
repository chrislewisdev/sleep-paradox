#pragma once

#include "world_object.h"
#include "rpg.h"
#include "enemy_type.h"

namespace sp {
    enum class enemy_state {
        idle,
        chase,
        attack,
        charge,
        bonk,
        trapped_player,
    };

    class world_object_enemy : public world_object {
        private:
            void update_idle(sp::world_state& world_state);
            void update_chase(sp::world_state& world_state);
            void enter_attack();
            void update_attack(sp::world_state& world_state);
            void update_charge(sp::world_state& world_state);
            void enter_bonk();
            void update_bonk(sp::world_state& world_state);
            void update_trap_player(sp::world_state& world_state);

            int get_windup_duration() const;
            int get_attack_distance_squared() const;

            const enemy_type* type;
            int health;

            enemy_state state = enemy_state::idle;
            int attack_windup;
            vec3 charge_vector;

        public:
            world_object_enemy(const enemy_type& _type, vec3 position);

            const rpg_stats& get_stats() const;
            int get_health() const;
            int get_xp_reward() const;
            bool is_active() const;

            void update(sp::world_state& world_state);
            void receive_attack(sp::world_state& world_state, const rpg_stats& attacker);
    };
}
