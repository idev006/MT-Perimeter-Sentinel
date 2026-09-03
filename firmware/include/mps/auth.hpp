#pragma once
#include "types.hpp"
#include <cstdint>
#include <deque>
#include <set>
#include <stdexcept>
#include <string>

namespace mps {

struct AuthenticatedEnvelope {
  Event event;
  std::string nonce;
  std::int64_t issued_ms{};
  std::string mac_hex;
};

class IMessageAuthenticator {
 public:
  virtual ~IMessageAuthenticator() = default;
  virtual std::string sign(const Event& event,
                           const std::string& nonce,
                           std::int64_t issued_ms) const = 0;
  virtual bool verify(const AuthenticatedEnvelope& envelope) const = 0;
};

class ReplayGuard {
 public:
  ReplayGuard(std::int64_t max_age_ms, std::size_t max_entries = 1024)
      : max_age_ms_(max_age_ms), max_entries_(max_entries) {
    if (max_age_ms_ <= 0 || max_entries_ == 0) throw std::invalid_argument("invalid replay-guard bounds");
  }

  bool accept(const std::string& source,
              const std::string& nonce,
              std::int64_t issued_ms,
              std::int64_t now_ms) {
    prune(now_ms);
    if (source.empty() || nonce.empty() || issued_ms > now_ms || now_ms - issued_ms > max_age_ms_) return false;
    const std::string token = source + "\x1f" + nonce;
    if (seen_.count(token) != 0) return false;
    if (entries_.size() >= max_entries_) return false;
    entries_.push_back({token, issued_ms});
    seen_.insert(token);
    return true;
  }

  bool accept(const std::string& nonce, std::int64_t issued_ms, std::int64_t now_ms) {
    return accept("GLOBAL", nonce, issued_ms, now_ms);
  }

  std::size_t size() const { return entries_.size(); }

 private:
  struct Entry { std::string token; std::int64_t issued_ms; };
  void prune(std::int64_t now_ms) {
    while (!entries_.empty() && now_ms >= entries_.front().issued_ms &&
           now_ms - entries_.front().issued_ms > max_age_ms_) {
      seen_.erase(entries_.front().token);
      entries_.pop_front();
    }
  }

  std::int64_t max_age_ms_;
  std::size_t max_entries_;
  std::deque<Entry> entries_;
  std::set<std::string> seen_;
};

}  // namespace mps
