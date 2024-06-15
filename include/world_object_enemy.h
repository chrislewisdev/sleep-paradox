#pragma once

#include "world_object.h"

namespace sp {
    enum class enemy_state {
        idle,
        chase,
        attack
    };

    class world_object_enemy : public world_object {
        private:
            void update_idle(sp::world_state& world_state);
            void update_chase(sp::world_state& world_state);
            void update_attack(sp::world_state& world_state);

            enemy_state state = enemy_state::idle;

        public:
            world_object_enemy(vec3 position);

            void update(sp::world_state& world_state);
    };
}
