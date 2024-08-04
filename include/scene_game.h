#pragma once

#include "bn_vector.h"
#include "bn_affine_bg_ptr.h"

#include "scene.h"
#include "scene_manager.h"
#include "world_state.h"

namespace sp {
    class scene_game : public scene {
        private:
            sp::scene_manager& scene_manager;
            sp::world_state& world_state;
            bn::affine_bg_ptr bg_layer_floor, bg_layer_ceiling;

        public:
            scene_game(sp::scene_manager& _scene_manager, sp::world_state& _world_state);
            void update();
    };
}

