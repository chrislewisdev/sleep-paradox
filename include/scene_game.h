#pragma once

#include "bn_affine_bg_ptr.h"

#include "scene.h"
#include "scene_manager.h"
#include "world_camera.h"
#include "world_object.h"

namespace sp {
    class scene_game : public scene {
        private:
            sp::scene_manager& scene_manager;
            world_camera camera;
            vec3 camera_target;
            world_object player;
            bn::affine_bg_ptr bg_layer_floor, bg_layer_ceiling;
            int heading;

        public:
            scene_game(sp::scene_manager& _scene_manager);
            void update();
    };
}

