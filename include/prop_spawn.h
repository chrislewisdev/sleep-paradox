#pragma once

#include "bn_core.h"
#include "bn_sprite_item.h"

namespace sp {
	class prop_spawn {
		public:
			const int16_t x;
			const int16_t y;
			const bn::sprite_item& sprite;
			constexpr prop_spawn(uint16_t _x, uint16_t _y, const bn::sprite_item& _sprite): x(_x), y(_y), sprite(_sprite) {}
	};
}
