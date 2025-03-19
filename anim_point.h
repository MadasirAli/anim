#pragma once
#include <cstdint>

#include "easers.h"

namespace anim {
  struct anim_point {
    uint32_t stamp = -1;

    float position[2] = { 0 };
    float scale[2] = { 0 };
    float angle = 0;
    uint32_t sprite = 0;

    ease pos_ease = ease::linear;
    ease scale_ease = ease::linear;
    ease angle_ease = ease::linear;

    // Define constexpr constructor for the point struct
    constexpr anim_point(uint32_t stamp, float x = 0, float y = 0, float scaleX = 0, float scaleY = 0, 
      float angle = 0, uint32_t sprite = 0,
      ease posEase = ease::linear, ease scaleEase = ease::linear, ease angleEase = ease::linear)
      :
      stamp(stamp), position{ x, y }, scale{scaleX, scaleY}, angle(angle), sprite(sprite),
      pos_ease(posEase), scale_ease(scaleEase), angle_ease(angleEase)
    {}

    constexpr anim_point() {};
  };
}