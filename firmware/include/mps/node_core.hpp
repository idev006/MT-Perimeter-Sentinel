#pragma once
#include "ports.hpp"

namespace mps {

class NodeCore {
 public:
  NodeCore(ITransport& transport, IEventStore& queue) : tx_(transport), queue_(queue) {}

  bool submit(const Event& event) {
    if (tx_.available()) {
      const auto result = tx_.send(event);
      if (result.accepted && durable_or_better(result.state)) return true;
    }
    return queue_.push(event);
  }

  std::size_t replay() {
    std::size_t sent = 0;
    while (tx_.available()) {
      const auto next = queue_.peek();
      if (!next) break;
      const auto result = tx_.send(*next);
      if (!result.accepted || !durable_or_better(result.state)) break;
      if (!queue_.pop()) break;
      ++sent;
    }
    return sent;
  }

 private:
  ITransport& tx_;
  IEventStore& queue_;
};

}  // namespace mps
