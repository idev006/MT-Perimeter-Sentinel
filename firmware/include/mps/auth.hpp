#pragma once
#include "types.hpp"
#include <cstdint>
#include <set>
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
  explicit ReplayGuard(std::int64_t max_age_ms) : max_age_ms_(max_age_ms) {}

  bool accept(const std::string& nonce, std::int64_t issued_ms, std::int64_t now_ms) {
    if (nonce.empty() || issued_ms > now_ms || now_ms - issued_ms > max_age_ms_) return false;
    return seen_.insert(nonce).second;
  }

 private:
  std::int64_t max_age_ms_;
  std::set<std::string> seen_;
};

}  // namespace mps
