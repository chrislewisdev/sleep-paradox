#include "scene_pause.h"

#include "bn_keypad.h"

#include "bn_regular_bg_items_pause_mockup.h"

namespace sp {
    scene_pause::scene_pause(sp::scene_manager& _scene_manager, sp::world_state& _world_state) :
        scene_manager(_scene_manager),
        world_state(_world_state),
        bg(bn::regular_bg_items::pause_mockup.create_bg(0, 0))
    {
        world_state.set_visible(false);
    }

    void scene_pause::update() {
        if (bn::keypad::b_pressed()) {
            scene_manager.queue_scene_change(sp::scene_id::gameplay);
        }
    }
}
