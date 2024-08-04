#include "bn_core.h"
#include "bn_unique_ptr.h"

#include "scene_manager.h"
#include "scene_title.h"

#include "advikku_global.h"
#include "advikku_setup.h"
#include "advikku_update.h"
#include "daedalus.h"

int main()
{
    bn::core::init();

    bn::unique_ptr<sp::world_state> world_state = bn::make_unique<sp::world_state>();
    sp::scene_manager scene_manager(*world_state);
    scene_manager.queue_scene_change(sp::scene_id::title);


    REG_SNDSTAT= SSTAT_ENABLE;
	// snd1 on left/right ; both full volume
	REG_SNDDMGCNT = SDMG_BUILD_LR(SDMG_SQR1 | SDMG_SQR2 | SDMG_WAVE | SDMG_NOISE, 6);
	// DMG ratio to 100%
	REG_SNDDSCNT= SDS_DMG100 | SDS_A100 | SDS_AR | SDS_AL | SDS_ATMR0 | SDS_ARESET | SDS_B100 | SDS_BR | SDS_BL |SDS_BTMR1 | SDS_BRESET;

	cell_song_setup(DaedalusSongStruct);

    while(true)
    {
        cell_song_update();
        scene_manager.process_scene_changes();
        scene_manager.update();
        bn::core::update();
    }
}
