#pragma once
#include "ports.hpp"
#include <algorithm>
#include <deque>
namespace mps {
class BoundedQueue final: public IEventStore {
 public:
  explicit BoundedQueue(std::size_t capacity):cap_(capacity){}
  bool push(const Event& e) override {
    if(items_.size()<cap_){items_.push_back(e); sort(); return true;}
    auto worst=std::max_element(items_.begin(),items_.end(),[](const Event&a,const Event&b){return static_cast<int>(a.priority)<static_cast<int>(b.priority);});
    if(worst!=items_.end() && static_cast<int>(e.priority)<static_cast<int>(worst->priority)){*worst=e; sort(); return true;}
    return false;
  }
  std::optional<Event> pop() override { if(items_.empty()) return std::nullopt; auto e=items_.front(); items_.pop_front(); return e; }
  std::size_t size() const override { return items_.size(); }
 private:
  void sort(){ std::stable_sort(items_.begin(),items_.end(),[](const Event&a,const Event&b){return static_cast<int>(a.priority)<static_cast<int>(b.priority);}); }
  std::size_t cap_; std::deque<Event> items_;
};
}
