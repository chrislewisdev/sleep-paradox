#pragma once

#include "bn_optional.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_item.h"

#include "world_camera.h"

namespace sp {
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

            virtual void update(const world_camera& camera);
    };
}

