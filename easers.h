#pragma once

namespace anim {
  enum class ease {
    linear,
    quad_in,
    quad_out,
    quad_in_out
  };

  struct linear_easer
  {
  public:
    float operator() (float t) const {
      return t;
    }
  };

  struct quad_in_easer
  {
  public:
    float operator() (float t) const {
      return t*t;
    }
  };

  struct quad_out_easer
  {
  public:
    float operator() (float t) const {
      return -t * (t - 2.0f);
    }
  };

  struct quad_in_out_easer
  {
  public:
    float operator() (float t) const {
      if (t < 0.5f) {
        return 2.0f * (t*t);
      }
      else {
        return (-2.0f * t * t) + (4.0f * t) - 1.0f;
      }
    }
  };

  struct interpolator {
  public:
    float operator() (float a, float b, float t, ease ease) {

      float newT = 0;

      switch (ease) {
      case ease::linear:
        newT = linear_easer()(t);
        break;
      case ease::quad_in:
        newT = quad_in_easer()(t);
        break;
      case ease::quad_out:
        newT = quad_out_easer()(t);
        break;
      case ease::quad_in_out:
        newT = quad_in_out_easer()(t);
        break;
      default:
        assert(false);
        break;
      }

      return a + (b - a) * newT;
    }
  };
}

