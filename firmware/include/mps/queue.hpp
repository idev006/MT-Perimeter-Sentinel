#pragma once
#include "ports.hpp"
#include <algorithm>
#include <deque>
#include <stdexcept>

namespace mps {

class BoundedQueue final : public IEventStore {
 public:
  explicit BoundedQueue(std::size_t capacity) : cap_(capacity) {
    if (capacity == 0) throw std::invalid_argument("queue capacity must be > 0");
  }

  bool push(const Event& e) override {
    if (items_.size() < cap_) {
      items_.push_back(e);
      sort_by_priority();
      return true;
    }

    auto worst = std::max_element(
        items_.begin(), items_.end(), [](const Event& a, const Event& b) {
          return static_cast<int>(a.priority) < static_cast<int>(b.priority);
        });

    if (worst != items_.end() &&
        static_cast<int>(e.priority) < static_cast<int>(worst->priority)) {
      *worst = e;
      ++evicted_count_;
      sort_by_priority();
      return true;
    }
    ++rejected_count_;
    return false;
  }

  std::optional<Event> peek() const override {
    if (items_.empty()) return std::nullopt;
    return items_.front();
  }

  bool pop() override {
    if (items_.empty()) return false;
    items_.pop_front();
    return true;
  }

  std::size_t size() const override { return items_.size(); }
  std::size_t capacity() const { return cap_; }
  std::size_t evicted_count() const { return evicted_count_; }
  std::size_t rejected_count() const { return rejected_count_; }

 private:
  void sort_by_priority() {
    std::stable_sort(items_.begin(), items_.end(), [](const Event& a, const Event& b) {
      return static_cast<int>(a.priority) < static_cast<int>(b.priority);
    });
  }

  std::size_t cap_;
  std::size_t evicted_count_{0};
  std::size_t rejected_count_{0};
  std::deque<Event> items_;
};

}  // namespace mps
