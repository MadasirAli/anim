#pragma once
#include <cstdint>

namespace anim {
  struct anim_state {
    float accumulation = 0;
    float norm = 0;
    uint32_t currentStemp = 0;
  };
}