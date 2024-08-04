#include "fx_callout.h"

namespace sp {
    constexpr int callout_lifetime = 60;

    fx_callout::fx_callout(const bn::sprite_text_generator& text_gen, bn::fixed_point point, const bn::string_view& text) {
        text_gen.generate(point, text, text_sprites);
        timer = callout_lifetime;
    }

    void fx_callout::update() {
        if (timer > 0) {
            timer--;

            for (bn::sprite_ptr& sprite : text_sprites) {
                sprite.set_y(sprite.y() - 1);
            }
        }
    }

    bool fx_callout::is_done() {
        return timer == 0;
    }
}
