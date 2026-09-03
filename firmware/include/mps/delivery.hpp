#pragma once
#include <cstdint>
#include <map>
#include <set>
#include <stdexcept>
#include <string>

namespace mps {

enum class SequenceStatus { ACCEPTED, DUPLICATE, STALE, GAP, WINDOW_EXCEEDED };

class DeliveryLedger {
 public:
  explicit DeliveryLedger(std::size_t max_pending_per_source = 256)
      : max_pending_per_source_(max_pending_per_source) {
    if (max_pending_per_source_ == 0) throw std::invalid_argument("sequence window must be > 0");
  }

  bool accept(const std::string& event_id) { return seen_ids_.insert(event_id).second; }

  SequenceStatus observe(const std::string& source, std::uint64_t sequence) {
    auto& state = sources_[source];
    if (!state.initialized) {
      state.initialized = true;
      state.contiguous = sequence;
      return SequenceStatus::ACCEPTED;
    }
    if (sequence <= state.contiguous) return SequenceStatus::STALE;
    if (state.pending.count(sequence) != 0) return SequenceStatus::DUPLICATE;

    const auto expected = state.contiguous + 1;
    if (sequence == expected) {
      state.contiguous = sequence;
      while (state.pending.erase(state.contiguous + 1) != 0) ++state.contiguous;
      return SequenceStatus::ACCEPTED;
    }

    if (state.pending.size() >= max_pending_per_source_) return SequenceStatus::WINDOW_EXCEEDED;
    state.pending.insert(sequence);
    return SequenceStatus::GAP;
  }

  std::uint64_t contiguous_sequence(const std::string& source) const {
    const auto it = sources_.find(source);
    return it == sources_.end() ? 0 : it->second.contiguous;
  }

  std::size_t pending_count(const std::string& source) const {
    const auto it = sources_.find(source);
    return it == sources_.end() ? 0 : it->second.pending.size();
  }

 private:
  struct SourceState {
    bool initialized{false};
    std::uint64_t contiguous{};
    std::set<std::uint64_t> pending;
  };
  std::size_t max_pending_per_source_;
  std::set<std::string> seen_ids_;
  std::map<std::string, SourceState> sources_;
};

}  // namespace mps
