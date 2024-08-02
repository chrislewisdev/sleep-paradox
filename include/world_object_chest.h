#pragma once

#include "world_object.h"
#include "interactable.h"

namespace sp {
    class world_object_chest : public world_object, public interactable {
        public:
            world_object_chest(const vec3& position);

            vec3 get_position() const;
            void interact(sp::world_state& world_state) const;
    };
}

