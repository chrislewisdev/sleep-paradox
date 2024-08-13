#pragma once

namespace sp {
    enum class scene_id {
        title,
        gameplay,
        pause,
        end,
        game_over,
    };

    class scene {
        public:
            virtual ~scene() = default;

            virtual void update() = 0;
    };
}

