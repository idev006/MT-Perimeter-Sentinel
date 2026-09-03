#pragma once
#include <optional>
#include <string>
#include <utility>

namespace mps {

enum class OtaState { IDLE, STAGED, BOOT_PENDING, COMMITTED, ROLLED_BACK, FAILED };

class SafeOta {
 public:
  explicit SafeOta(std::string active) : active_(std::move(active)) {}

  const std::string& active() const { return active_; }
  OtaState state() const { return state_; }

  bool stage(const std::string& candidate, bool signature_ok, bool compatible) {
    if (candidate.empty() || candidate == active_ || !signature_ok || !compatible) {
      state_ = OtaState::FAILED;
      return false;
    }
    candidate_ = candidate;
    state_ = OtaState::STAGED;
    return true;
  }

  bool boot_candidate(bool self_test_ok) {
    if (!candidate_ || state_ != OtaState::STAGED) return false;
    if (!self_test_ok) {
      candidate_.reset();
      state_ = OtaState::ROLLED_BACK;
      return false;
    }
    previous_ = active_;
    active_ = *candidate_;
    candidate_.reset();
    state_ = OtaState::BOOT_PENDING;
    return true;
  }

  bool commit() {
    if (state_ != OtaState::BOOT_PENDING) return false;
    state_ = OtaState::COMMITTED;
    return true;
  }

  bool rollback() {
    if (!previous_) return false;
    active_ = *previous_;
    previous_.reset();
    candidate_.reset();
    state_ = OtaState::ROLLED_BACK;
    return true;
  }

  bool install(const std::string& candidate, bool signed_ok, bool self_test_ok) {
    if (!stage(candidate, signed_ok, true)) return false;
    if (!boot_candidate(self_test_ok)) return false;
    return commit();
  }

 private:
  std::string active_;
  std::optional<std::string> previous_;
  std::optional<std::string> candidate_;
  OtaState state_{OtaState::IDLE};
};

}  // namespace mps
