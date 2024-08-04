#pragma once

#include "bn_vector.h"
#include "bn_sprite_ptr.h"
#include "bn_fixed_point.h"
#include "bn_sprite_text_generator.h"

namespace sp {
    class fx_callout {
        private:
            bn::vector<bn::sprite_ptr, 2> text_sprites;
            int timer;

        public:
            fx_callout(const bn::sprite_text_generator& text_gen, bn::fixed_point point, const bn::string_view& text);

            void update();
            bool is_done();
    };
}
