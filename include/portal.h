#pragma once

#include "bn_string_view.h"

namespace sp {
    class portal {
        public:
            const bn::string_view target_zone_name;
            const int16_t x, y;
            const int16_t width, height;
            const int16_t destination_x, destination_y;

            constexpr portal(
                const bn::string_view& _target_zone_name,
                int16_t _x,
                int16_t _y,
                int16_t _width,
                int16_t _height,
                int16_t _destination_x,
                int16_t _destination_y
            ) :
                target_zone_name(_target_zone_name),
                x(_x),
                y(_y),
                width(_width),
                height(_height),
                destination_x(_destination_x),
                destination_y(_destination_y)
            {}
    };
}

