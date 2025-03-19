#include "delta_fixed_step.h"

using namespace anim;

delta_fixed_step::delta_fixed_step(float duration, uint32_t maxStemp) :
  duration(duration),
  maxStemp(maxStemp)
{}

void delta_fixed_step::tick(float step, state& state) const
{
  state.accumulation += step;
}

void delta_fixed_step::reset(state& state) const
{
  state.accumulation = 0;
}

uint32_t delta_fixed_step::get(const state& state) const
{
  return (uint32_t)((state.accumulation / duration) * maxStemp);
}
