#pragma once

#include "bn_optional.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_item.h"
#include "bn_sprite_animate_actions.h"
#include "bn_string_view.h"
#include "bn_fixed_rect.h"

#include "vec3.h"
#include "world_camera.h"

namespace sp {
    using world_object_animation = bn::sprite_animate_action<10>;
    using animation_generator = bn::sprite_animate_action<10> (*)(const bn::sprite_ptr&);

    // Declared to avoid circular dependency with world_state.h
    class world_state;

    class world_object {
        protected:
            vec3 test_movement(sp::world_state& world_state, vec3 movement);

            vec3 position;
            bn::optional<bn::sprite_ptr> sprite;
            const bn::sprite_item& sprite_item;
            bn::optional<world_object_animation> animation;
            bn::string_view current_animation_name;

        public:
            world_object(const bn::sprite_item& _sprite_item);
            virtual ~world_object() = default;

            const vec3& get_position() const;
            void set_position(const vec3& _position);
            vec3 get_screen_position(const world_camera& camera) const;
            bn::fixed_rect get_collider() const;

            void use_animation(const bn::string_view& name, animation_generator generator);

            virtual void update(sp::world_state& world_state);
    };
}

