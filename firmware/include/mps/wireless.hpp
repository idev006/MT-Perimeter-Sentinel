#pragma once
#include <optional>
#include <string>
#include <utility>

namespace mps {

class WirelessProfileManager {
 public:
  explicit WirelessProfileManager(std::string active) : active_(std::move(active)) {}

  const std::string& active() const { return active_; }
  const std::optional<std::string>& previous() const { return previous_; }
  const std::optional<std::string>& candidate() const { return candidate_; }

  bool stage(const std::string& profile) {
    if (profile.empty() || profile == active_) return false;
    candidate_ = profile;
    return true;
  }

  bool test_candidate(bool trusted_gateway_ok) const {
    return candidate_.has_value() && trusted_gateway_ok;
  }

  bool commit_candidate() {
    if (!candidate_) return false;
    previous_ = active_;
    active_ = *candidate_;
    candidate_.reset();
    return true;
  }

  bool revoke_previous() {
    if (!previous_) return false;
    previous_.reset();
    return true;
  }

  bool migrate(const std::string& profile, bool trusted_gateway_ok) {
    if (!stage(profile)) return false;
    if (!test_candidate(trusted_gateway_ok)) {
      candidate_.reset();
      return false;
    }
    return commit_candidate();
  }

 private:
  std::string active_;
  std::optional<std::string> previous_;
  std::optional<std::string> candidate_;
};

}  // namespace mps
