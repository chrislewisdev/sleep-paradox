#pragma once

#include "world_object.h"

namespace sp {
    class world_object_projectile : public world_object {
        private:
            vec3 velocity;
            bool active;
            animation_generator animation;

        public:
            world_object_projectile(vec3 _position, vec3 _velocity, animation_generator _animation);

            bool is_active() const;

            void update(sp::world_state& world_state);
    };
}

