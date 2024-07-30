#pragma once

#include "sp_zone_sample_8x8.h"
#include "sp_zone_alternate.h"
#include "sp_zone_corridor1.h"

namespace sp {
    constexpr const world_zone* get_zone_by_name(const bn::string_view& name) {
        if (name == "sample_8x8") return &sp::zone_sample_8x8::zone;
        if (name == "alternate") return &sp::zone_alternate::zone;
        if (name == "corridor1") return &sp::zone_corridor1::zone;

        return &sp::zone_sample_8x8::zone;
    }
}

