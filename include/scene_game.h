#pragma once

#include "bn_vector.h"
#include "bn_affine_bg_ptr.h"

#include "scene.h"
#include "scene_manager.h"
#include "world_camera.h"
#include "world_object.h"
#include "world_object_player.h"

namespace sp {
    class scene_game : public scene {
        private:
            sp::scene_manager& scene_manager;
            world_camera camera;
            world_object_player player;
            vec3 camera_target;
            bn::affine_bg_ptr bg_layer_floor, bg_layer_ceiling;

        public:
            scene_game(sp::scene_manager& _scene_manager);
            void update();
    };
}

