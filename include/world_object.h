#pragma once

#include "bn_optional.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_item.h"

#include "vec3.h"

namespace sp {
    // Declared to avoid circular dependency with world_state.h
    class world_state;

    class world_object {
        protected:
            vec3 position;
            bn::optional<bn::sprite_ptr> sprite;
            const bn::sprite_item& sprite_item;

        public:
            world_object(const bn::sprite_item& _sprite_item);
            virtual ~world_object() = default;

            const vec3& get_position() const;
            void set_position(const vec3& _position);

            virtual void update(sp::world_state& world_state);
    };
}

