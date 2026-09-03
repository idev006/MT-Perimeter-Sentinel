#pragma once
#include "topology.hpp"
#include <vector>

namespace mps {

enum class Direction { UNKNOWN, CLOCKWISE, COUNTER_CLOCKWISE };

class Correlator {
 public:
  explicit Correlator(RingTopology topology) : topology_(topology) {}

  Direction direction(const std::vector<int>& path) const {
    if (path.size() < 2) return Direction::UNKNOWN;

    Direction direction = Direction::UNKNOWN;
    for (std::size_t i = 1; i < path.size(); ++i) {
      const int from = path[i - 1];
      const int to = path[i];
      if (!topology_.adjacent(from, to)) return Direction::UNKNOWN;

      const auto step = topology_.clockwise_step(from, to)
                            ? Direction::CLOCKWISE
                            : Direction::COUNTER_CLOCKWISE;
      if (direction == Direction::UNKNOWN) direction = step;
      else if (direction != step) return Direction::UNKNOWN;
    }
    return direction;
  }

 private:
  RingTopology topology_;
};

}  // namespace mps
