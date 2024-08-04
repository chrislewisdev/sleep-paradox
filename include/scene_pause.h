#pragma once

#include "bn_regular_bg_ptr.h"

#include "scene.h"
#include "scene_manager.h"
#include "world_state.h"

namespace sp {
    class scene_pause : public scene {
        private:
            sp::scene_manager& scene_manager;
            sp::world_state& world_state;
            bn::regular_bg_ptr bg;

        public:
            scene_pause(sp::scene_manager& _scene_manager, sp::world_state& _world_state);

            void update();
    };
}

