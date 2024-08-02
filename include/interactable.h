#pragma once

#include "vec3.h"

namespace sp {
    class world_state;

    class interactable {
        public:
            virtual ~interactable() = default;

            virtual vec3 get_position() const = 0;
            virtual void interact(sp::world_state& world_state) const = 0;
    };
}

