#pragma once
#include <cstdint>
#include <map>
#include <set>
#include <string>

namespace mps {

enum class SequenceStatus { ACCEPTED, DUPLICATE, STALE, GAP };

class DeliveryLedger {
 public:
  bool accept(const std::string& event_id) { return seen_ids_.insert(event_id).second; }

  SequenceStatus observe(const std::string& source, std::uint64_t sequence) {
    auto it = last_sequence_.find(source);
    if (it == last_sequence_.end()) {
      last_sequence_[source] = sequence;
      return SequenceStatus::ACCEPTED;
    }
    if (sequence == it->second) return SequenceStatus::DUPLICATE;
    if (sequence < it->second) return SequenceStatus::STALE;
    const auto expected = it->second + 1;
    it->second = sequence;
    return sequence == expected ? SequenceStatus::ACCEPTED : SequenceStatus::GAP;
  }

 private:
  std::set<std::string> seen_ids_;
  std::map<std::string, std::uint64_t> last_sequence_;
};

}  // namespace mps
