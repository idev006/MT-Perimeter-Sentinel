#pragma once
#include <algorithm>
#include <map>
#include <string>
#include <vector>

namespace mps {

struct Observation {
  std::string sensor_type;
  double confidence{};
  long long at_ms{};
};

class SensorFusion {
 public:
  static double fuse(const std::vector<Observation>& observations,
                     long long now_ms,
                     long long window_ms) {
    if (window_ms < 0) return 0.0;

    std::map<std::string, double> best_by_type;
    for (const auto& observation : observations) {
      if (observation.sensor_type.empty()) continue;
      if (observation.confidence < 0.0 || observation.confidence > 1.0) continue;
      if (observation.at_ms > now_ms) continue;
      if (now_ms - observation.at_ms > window_ms) continue;

      auto [it, inserted] = best_by_type.emplace(observation.sensor_type, observation.confidence);
      if (!inserted) it->second = std::max(it->second, observation.confidence);
    }

    if (best_by_type.empty()) return 0.0;
    double sum = 0.0;
    for (const auto& [_, confidence] : best_by_type) sum += confidence;
    return sum / static_cast<double>(best_by_type.size());
  }
};

}  // namespace mps
