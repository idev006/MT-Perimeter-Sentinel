#include "mps/host_auth.hpp"
#include <openssl/crypto.h>
#include <openssl/hmac.h>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <utility>

namespace mps {
namespace {
std::string canonical(const Event& event, const std::string& nonce, std::int64_t issued_ms) {
  std::ostringstream out;
  out << event.schema_version << '|'
      << event.id << '|'
      << event.source << '|'
      << event.sequence << '|'
      << static_cast<int>(event.priority) << '|'
      << event.type << '|'
      << event.occurred_ms << '|'
      << nonce << '|'
      << issued_ms;
  return out.str();
}

std::string hmac_hex(const std::string& key, const std::string& message) {
  unsigned int length = 0;
  unsigned char digest[EVP_MAX_MD_SIZE];
  if (HMAC(EVP_sha256(), key.data(), static_cast<int>(key.size()),
           reinterpret_cast<const unsigned char*>(message.data()), message.size(),
           digest, &length) == nullptr) {
    throw std::runtime_error("HMAC failed");
  }
  std::ostringstream out;
  out << std::hex << std::setfill('0');
  for (unsigned int i = 0; i < length; ++i) out << std::setw(2) << static_cast<int>(digest[i]);
  return out.str();
}
}  // namespace

OpenSslHmacSha256Authenticator::OpenSslHmacSha256Authenticator(std::string key) : key_(std::move(key)) {
  if (key_.empty()) throw std::invalid_argument("HMAC key must not be empty");
}

std::string OpenSslHmacSha256Authenticator::sign(const Event& event,
                                                   const std::string& nonce,
                                                   std::int64_t issued_ms) const {
  return hmac_hex(key_, canonical(event, nonce, issued_ms));
}

bool OpenSslHmacSha256Authenticator::verify(const AuthenticatedEnvelope& envelope) const {
  const auto expected = sign(envelope.event, envelope.nonce, envelope.issued_ms);
  if (expected.size() != envelope.mac_hex.size()) return false;
  return CRYPTO_memcmp(expected.data(), envelope.mac_hex.data(), expected.size()) == 0;
}

}  // namespace mps
