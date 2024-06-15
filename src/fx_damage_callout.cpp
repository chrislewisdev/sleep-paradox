#include "fx_damage_callout.h"

#include "bn_string.h"

namespace sp {
    constexpr int callout_lifetime = 60;

    fx_damage_callout::fx_damage_callout(const bn::sprite_text_generator& text_gen, bn::fixed_point point, int amount, bool is_weak) {
        text_gen.generate(point, bn::to_string<4>(amount), text_sprites);
        timer = callout_lifetime;
    }

    void fx_damage_callout::update() {
        if (timer > 0) {
            timer--;

            for (bn::sprite_ptr& sprite : text_sprites) {
                sprite.set_y(sprite.y() - 1);
            }
        }
    }

    bool fx_damage_callout::is_done() {
        return timer == 0;
    }
}
