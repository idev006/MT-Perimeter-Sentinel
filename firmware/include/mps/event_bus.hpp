#pragma once
#include "types.hpp"
#include <functional>
#include <vector>
namespace mps {
class EventBus {
 public:
  using Handler=std::function<void(const Event&)>;
  void subscribe(Handler h){ handlers_.push_back(std::move(h)); }
  void publish(const Event& e) const { for(const auto& h:handlers_) h(e); }
 private: std::vector<Handler> handlers_;
};
}
