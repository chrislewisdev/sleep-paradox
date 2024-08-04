#pragma once

#include "world_object.h"
#include "interactable.h"
#include "item.h"

namespace sp {
    class world_object_chest : public world_object, public interactable {
        private:
            const sp::item_id item_id;
            bool is_opened = false;

        public:
            world_object_chest(const vec3& position, sp::item_id item_id);

            vec3 get_position() const;
            bool get_is_opened() const;
            void interact(sp::world_state& world_state) const;
            void activate(sp::world_state& world_state);
    };
}

