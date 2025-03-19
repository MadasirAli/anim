#pragma once
#include <cstdint>

namespace anim {
  class delta_fixed_step
  {
  public:
    struct state {
      float accumulation = 0;
    };

  public:
    delta_fixed_step(float duration, uint32_t maxStemp);

    void tick(float step, state& state) const;
    void reset(state& state) const;
    uint32_t get(const state& state) const;

  public:
    const float duration;
    const uint32_t maxStemp;
  };
}