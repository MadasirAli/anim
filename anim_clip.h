#pragma once

#include <array>
#include <cmath>
#include <assert.h>

namespace anim {

  template<size_t N = 100, size_t PointsCount = 32>
  class anim_clip
  {
  public:
    struct point {
      uint32_t stamp = 0;

      float position[2] = { 0 };
      float angle = 0;
      uint32_t sprite = 0;
    };
  public:
    constexpr anim_clip() {
      for (uint32_t i = 0; i < PointsCount; ++i) {
        assert(points[i].stamp <= N);
      }
    }

    void tick(float dt) {
      _accumulation += dt;

      if (loop) {
        _accumulation = fmod(_accumulation, duration);
      }
      else {
        _accumulation = _accumulation > duration ? duration : _accumulation;
      }

      _currentStemp = (uint32_t)((_accumulation / duration) * N);
      assert(_currentStemp <= N);
    }
    point get() {
      for (size_t i = 0; i < PointsCount; ++i) {
        if (points[i].stamp == _currentStemp) {
          if (_currentStemp != N) {
            point next = points[i + 1];
            
            float norm = (_accumulation - ((duration / (float)N) * _currentStemp)) 
              / (((duration / (float)N) * next.stamp) - ((duration / (float)N) * _currentStemp));

            next.position[0] *= norm;
            next.position[1] *= norm;
            next.angle *= norm;

            return next;
          }
          else {
            return points[i];
          }
        }
      }

      assert(false);
    }
    void reset() {
      _accumulation = 0;
      _currentStemp = 0;
    }

    float get_time() const {
      return _accumulation;
    }
    uint32_t get_stemp() const {
      return _currentStemp;
    }

  public:
    bool pos_enabled = true;
    bool angle_enabled = true;
    bool sprite_enabled = true;

    bool loop = true;
    float duration = 0;

    std::array<point, PointsCount> points = { 0 };

    const size_t resolution = N;
    const size_t pointCount = pointCount;

  private:
    float _accumulation = 0;
    uint32_t _currentStemp = 0;
  };
}