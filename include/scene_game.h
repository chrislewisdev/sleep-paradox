#pragma once

#include "bn_vector.h"
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
            bn::vector<world_object, 10> objects;
            bn::affine_bg_ptr bg_layer_floor, bg_layer_ceiling;
            int heading;
            int timer;

        public:
            scene_game(sp::scene_manager& _scene_manager);
            void update();
    };
}

