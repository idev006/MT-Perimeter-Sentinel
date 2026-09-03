#pragma once
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>

namespace mps {

struct Config {
  int version{};
  std::string profile;
};

class TransactionalConfig {
 public:
  explicit TransactionalConfig(Config active) : active_(std::move(active)) { validate(active_); }

  const Config& active() const { return active_; }
  const std::optional<Config>& candidate() const { return candidate_; }

  bool stage_candidate(const Config& candidate) {
    validate(candidate);
    if (candidate.version <= active_.version) {
      candidate_.reset();
      return false;
    }
    candidate_ = candidate;
    return true;
  }

  bool test_candidate(bool connectivity_ok) const { return candidate_.has_value() && connectivity_ok; }

  bool commit_candidate() {
    if (!candidate_) return false;
    previous_ = active_;
    active_ = *candidate_;
    candidate_.reset();
    return true;
  }

  bool apply_candidate(const Config& candidate, bool connectivity_ok) {
    if (!stage_candidate(candidate)) return false;
    if (!test_candidate(connectivity_ok)) {
      candidate_.reset();
      return false;
    }
    return commit_candidate();
  }

  bool rollback() {
    if (!previous_) return false;
    const auto current = active_;
    active_ = *previous_;
    previous_ = current;
    candidate_.reset();
    return true;
  }

 private:
  static void validate(const Config& config) {
    if (config.version < 0) throw std::invalid_argument("config version must be non-negative");
    if (config.profile.empty()) throw std::invalid_argument("config profile must not be empty");
  }

  Config active_;
  std::optional<Config> candidate_;
  std::optional<Config> previous_;
};

}  // namespace mps
