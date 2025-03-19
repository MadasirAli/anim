#pragma once

#include <array>
#include <cmath>
#include <assert.h>
#include <iostream>

#include "anim_point.h"
#include "anim_state.h"
#include "easers.h"

namespace anim {

  template<size_t PointsCount, size_t N = 100>
  class anim_clip
  {
  public:
    constexpr anim_clip(bool posSwitch, bool scaleSwitch, bool rotSwitch, bool spriteSwitch,
      bool loop, float duration, 
      ease posEase, ease rotEase, ease scaleEase,
      std::array<anim_point, PointsCount> init_points)
      : 
      pos_enabled(posSwitch),
      scale_enabled(scaleSwitch),
      angle_enabled(rotSwitch),
      sprite_enabled(spriteSwitch),
      loop(loop),
      duration(duration),
      pos_ease(posEase),
      rot_ease(rotEase),
      scale_ease(scaleEase),
      points(init_points) 
    {
      // "There must be point at the start and at the end with minimum and maximum stemps."
      assert(PointsCount >= 2);
      assert(init_points[0].stamp == 0 && init_points[PointsCount-1].stamp == N);
    }

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

      for (size_t i = 1; i < PointsCount; ++i) {
        if (points[i].stamp > currentStemp) {
          anim_point current = points[i-1];

          if (currentStemp != N) {
            anim_point next = points[i];
            
            float norm = (accumulation - ((duration / (float)N) * current.stamp)) 
              / (((duration / (float)N) * next.stamp) - ((duration / (float)N) * current.stamp));

            std::cout << "Norm: " << norm << "\n";
            std::cout << "Stemp: " << currentStemp << "\n";

            next.position[0] = interpolator()(current.position[0], next.position[0], norm, pos_ease);
            next.position[1] = interpolator()(current.position[1], next.position[1], norm, pos_ease);
           
            next.scale[0] = interpolator()(current.scale[0], next.scale[0], norm, scale_ease);
            next.scale[1] = interpolator()(current.scale[1], next.scale[1], norm, scale_ease);
            next.angle = interpolator()(current.angle, next.angle, norm, rot_ease);

            next.sprite = current.sprite;

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

    ease pos_ease = ease::linear;
    ease rot_ease = ease::linear;
    ease scale_ease = ease::linear;

    std::array<anim_point, PointsCount> points;

    const size_t resolution = N;
    const size_t pointCount = PointsCount;
  };
}