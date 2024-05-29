#ifndef SCENE_H
#define SCENE_H

namespace sp {
    enum class scene_id {
        title,
    };

    class scene {
        public:
            virtual ~scene() = default;

            virtual void update() = 0;
    };
}

#endif
