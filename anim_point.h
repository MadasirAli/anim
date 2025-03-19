#pragma once
#include <cstdint>

namespace anim {
  struct anim_point {
    uint32_t stamp = -1;

    float position[2] = { 0 };
    float scale[2] = { 0 };
    float angle = 0;
    uint32_t sprite = 0;

    // Define constexpr constructor for the point struct
    constexpr anim_point(uint32_t stamp, float x, float y, float scaleX, float scaleY, 
      float angle, uint32_t sprite)
      : stamp(stamp), position{ x, y }, scale{scaleX, scaleY}, angle(angle), sprite(sprite) {
    }
  };
}