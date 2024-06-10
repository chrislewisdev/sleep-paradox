#pragma once

#include "bn_optional.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_item.h"
#include "bn_sprite_animate_actions.h"
#include "bn_string_view.h"

#include "vec3.h"

namespace sp {
    // Declared to avoid circular dependency with world_state.h
    class world_state;

    class world_object {
        protected:
            vec3 position;
            bn::optional<bn::sprite_ptr> sprite;
            const bn::sprite_item& sprite_item;
            bn::optional<bn::sprite_animate_action<10>> animation;
            bn::string_view current_animation_name;

        public:
            world_object(const bn::sprite_item& _sprite_item);
            virtual ~world_object() = default;

            const vec3& get_position() const;
            void set_position(const vec3& _position);

            void use_animation(const bn::string_view& name, bn::sprite_animate_action<10> (*generator)(const bn::sprite_ptr&));

            virtual void update(sp::world_state& world_state);
    };
}

