#include "scene_title.h"

#include "bn_keypad.h"

#include "institutionalised.h"
#include "donotsaygoodnight.h"

#include "bn_regular_bg_items_title.h"
#include "bn_regular_bg_items_gbajam_logo.h"

namespace sp {
    scene_title::scene_title(sp::scene_manager& _scene_manager) :
        scene_manager(_scene_manager),
        bg(bn::regular_bg_items::gbajam_logo.create_bg(0, 0))
    {
        cell_song_setup(donotsaygoodnightSongStruct);
    }

    void scene_title::update() {
        if (timer > 0) {
            timer--;
            if (timer == 0) bg = bn::regular_bg_items::title.create_bg(0, 0);
        }

        if (timer == 0 && (bn::keypad::a_held() || bn::keypad::start_held())) {
            scene_manager.queue_scene_change(sp::scene_id::gameplay);
            // cell_song_setup(InstitutionalisedSongStruct);
        }
    }
}
