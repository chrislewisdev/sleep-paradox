#pragma once

#include "world_object.h"

namespace sp {
    class world_object_player : public world_object {
        private:
            vec3 get_movement_input(bn::fixed heading);
        public:
            world_object_player();

            void update(sp::world_state& world_state);
    };
}
