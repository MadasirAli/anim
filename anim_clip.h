#pragma once

#include <array>
#include <cmath>
#include <assert.h>

#include "anim_point.h"
#include "anim_state.h"

namespace anim {

  template<size_t N = 100, size_t PointsCount = 32>
  class anim_clip
  {
  public:
    // Define constexpr constructor for anim_clip that accepts an initializer list
    constexpr anim_clip(bool posSwitch, bool scaleSwitch, bool rotSwitch, bool spriteSwitch,
      bool loop, float duration, std::array<anim_point, PointsCount> init_points)
      : 
      pos_enabled(posSwitch),
      scale_enabled(scaleSwitch),
      angle_enabled(rotSwitch),
      sprite_enabled(spriteSwitch),
      loop(loop),
      duration(duration),
      points(init_points) 
    {}

    void tick(float dt, anim_state& state) const {
      state.accumulation += dt;

      if (loop) {
        state.accumulation = fmod(state.accumulation, duration);
      }
      else {
        state.accumulation = state.accumulation > duration ? duration : state.accumulation;
      }

      state.currentStemp = (uint32_t)((state.accumulation / duration) * N);
      assert(state.currentStemp <= N);
    }
    anim_point get(const anim_state& state) const {
      const auto accumulation = state.accumulation;
      const auto currentStemp = state.currentStemp;

      for (size_t i = 0; i < PointsCount; ++i) {
        if (points[i].stamp == currentStemp) {
          anim_point current = points[i];

          if (currentStemp != N) {
            anim_point next = points[i + 1];
            
            float norm = (accumulation - ((duration / (float)N) * currentStemp)) 
              / (((duration / (float)N) * next.stamp) - ((duration / (float)N) * currentStemp));

            next.position[0] = current.position[0] + (next.position[0] - next.position[0]) * norm;
            next.position[1] = current.position[1] + (next.position[1] - next.position[1]) * norm;
            next.scale[0]    = current.scale[0]    + (next.scale[0]    - next.scale[0])    * norm;
            next.scale[1]    = current.scale[1]    + (next.scale[1]    - next.scale[1])    * norm;
            next.angle       = current.angle       + (next.angle       - current.angle)    * norm;

            return next;
          }

          return current;
        }
      }

      assert(false);

      return anim_point{};
    }
    void reset(anim_state& state) const {
      state.accumulation = 0;
      state.currentStemp = 0;
    }
  public:
    bool pos_enabled = true;
    bool scale_enabled = true;
    bool angle_enabled = true;
    bool sprite_enabled = true;

    bool loop = true;
    float duration = 0;

    std::array<anim_point, PointsCount> points = { 0 };

    const size_t resolution = N;
    const size_t pointCount = PointsCount;
  };
}