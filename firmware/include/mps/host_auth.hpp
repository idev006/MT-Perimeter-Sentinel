#pragma once
#include "auth.hpp"
#include <string>

namespace mps {

class OpenSslHmacSha256Authenticator final : public IMessageAuthenticator {
 public:
  explicit OpenSslHmacSha256Authenticator(std::string key);
  std::string sign(const Event& event,
                   const std::string& nonce,
                   std::int64_t issued_ms) const override;
  bool verify(const AuthenticatedEnvelope& envelope) const override;

 private:
  std::string key_;
};

}  // namespace mps
