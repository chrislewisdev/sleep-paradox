#pragma once

namespace sp {
    class world_zone;

    class portal {
        public:
            const world_zone& target_zone;
            const int x, y;
            const int width, height;
            const int destination_x, destination_y;

            constexpr portal(
                const world_zone& _target_zone,
                int _x,
                int _y,
                int _width,
                int _height,
                int _destination_x,
                int _destination_y
            ) :
                target_zone(_target_zone),
                x(_x),
                y(_y),
                width(_width),
                height(_height),
                destination_x(_destination_x),
                destination_y(_destination_y)
            {}
    };
}

