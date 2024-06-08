#pragma once

#include "bn_vector.h"

#include "world_zone.h"
#include "world_camera.h"
#include "world_object_player.h"
#include "world_object_wall.h"

namespace sp {
    class world_state {
        private:
            const world_zone* current_zone;
            world_camera camera;
            world_object_player player;
            bn::vector<world_object_wall, 64> walls;

        public:
            world_state();

            const world_zone& get_current_zone() const;
            world_camera& get_camera();
            world_object_player& get_player();

            void update();
            void load_zone(const world_zone& zone);
    };
}
