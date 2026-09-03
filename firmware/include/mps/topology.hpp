#pragma once
#include <cstdlib>
#include <stdexcept>

namespace mps {

class RingTopology {
 public:
  explicit RingTopology(int nodes) : nodes_(nodes) {
    if (nodes < 3) throw std::invalid_argument("ring topology requires at least 3 nodes");
  }

  int size() const { return nodes_; }
  bool valid(int node) const { return node >= 1 && node <= nodes_; }

  bool adjacent(int a, int b) const {
    if (!valid(a) || !valid(b) || a == b) return false;
    const int delta = std::abs(a - b);
    return delta == 1 || delta == nodes_ - 1;
  }

  bool clockwise_step(int a, int b) const {
    if (!adjacent(a, b)) return false;
    return b == (a % nodes_) + 1;
  }

  bool counter_clockwise_step(int a, int b) const {
    if (!adjacent(a, b)) return false;
    return a == (b % nodes_) + 1;
  }

 private:
  int nodes_;
};

}  // namespace mps
