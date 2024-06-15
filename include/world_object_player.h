#pragma once

#include "world_object.h"
#include "rpg.h"

namespace sp {
    class world_object_player : public world_object {
        private:
            vec3 get_movement_input(bn::fixed heading);

            rpg_stats stats;
            int health;

        public:
            world_object_player();

            const rpg_stats& get_stats() const;

            void update(sp::world_state& world_state);
            void receive_attack(sp::world_state& world_state, const rpg_stats& attacker);
    };
}
