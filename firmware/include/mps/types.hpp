#pragma once
#include <cstdint>
#include <string>

namespace mps {

enum class Priority : int { P0 = 0, P1 = 1, P2 = 2, P3 = 3, P4 = 4 };

enum class DeliveryState : int {
  FAILED = 0,
  RECEIVED_LOCAL = 1,
  DURABLE_LOCAL = 2,
  DELIVERED_EXTERNAL = 3,
  PROCESSED_EXTERNAL = 4
};

struct Event {
  std::string id;
  std::string source;
  std::uint64_t sequence{};
  Priority priority{Priority::P2};
  std::string type;
  std::int64_t occurred_ms{};
  std::uint32_t schema_version{1};
};

struct SendResult {
  bool accepted{false};
  DeliveryState state{DeliveryState::FAILED};
};

inline bool durable_or_better(DeliveryState state) {
  return static_cast<int>(state) >= static_cast<int>(DeliveryState::DURABLE_LOCAL);
}

}  // namespace mps
