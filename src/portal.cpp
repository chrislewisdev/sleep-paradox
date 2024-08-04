#include "portal.h"

#include "world_state.h"

namespace sp {
    vec3 portal::get_position() const {
        return vec3(x + width/2, 16, y - height/2);
    }

    void portal::interact(sp::world_state& world_state) const {
        world_state.queue_zone_change(*this);
    }
}
