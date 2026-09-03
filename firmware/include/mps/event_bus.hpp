#pragma once
#include "types.hpp"
#include <cstddef>
#include <functional>
#include <utility>
#include <vector>

namespace mps {

class EventBus {
 public:
  using Handler = std::function<void(const Event&)>;

  std::size_t subscribe(Handler handler) {
    handlers_.push_back(std::move(handler));
    return handlers_.size() - 1;
  }

  void publish(const Event& event) const {
    for (const auto& handler : handlers_) handler(event);
  }

  std::size_t subscriber_count() const { return handlers_.size(); }

 private:
  std::vector<Handler> handlers_;
};

}  // namespace mps
