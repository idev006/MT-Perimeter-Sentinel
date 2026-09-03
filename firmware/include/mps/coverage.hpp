#pragma once
#include <cmath>

namespace mps {

struct CoveragePolicy {
  static bool valid_ratio(double value) {
    return std::isfinite(value) && value >= 0.0 && value <= 1.0;
  }

  static bool allow_disruptive_action(double projected, double minimum) {
    if (!valid_ratio(projected) || !valid_ratio(minimum)) return false;
    return projected >= minimum;
  }
};

}  // namespace mps
