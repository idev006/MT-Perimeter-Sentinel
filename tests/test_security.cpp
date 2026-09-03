#include "mps/auth.hpp"
#include "mps/command.hpp"
#include "mps/host_auth.hpp"
#include "mps/security.hpp"
#include <cassert>
#include <stdexcept>
using namespace mps;
int main() {
  assert(authorized(Role::VIEWER, Action::VIEW_STATUS));
  assert(!authorized(Role::VIEWER, Action::REBOOT_NODE));
  assert(authorized(Role::ENGINEER, Action::REBOOT_NODE));
  assert(!authorized(Role::ENGINEER, Action::ROTATE_CREDENTIALS));
  assert(authorized(Role::SECURITY_ADMIN, Action::ROTATE_CREDENTIALS));

  AuditedCommandService commands;
  assert(commands.execute("c1", "reboot:N01", Role::ENGINEER, Action::REBOOT_NODE) == "OK");
  assert(commands.execute("c1", "reboot:N01", Role::ENGINEER, Action::REBOOT_NODE) == "OK");
  assert(commands.audit().back().replayed);
  bool denied=false;
  try { commands.execute("c2", "rotate:secret-material", Role::VIEWER, Action::ROTATE_CREDENTIALS); }
  catch (const std::runtime_error&) { denied=true; }
  assert(denied);
  assert(commands.audit().back().result == "DENIED");

  Event e{"evt-auth", "N01", 9, Priority::P0, "INTRUSION", 100, 1};
  OpenSslHmacSha256Authenticator auth("test-key-not-production");
  AuthenticatedEnvelope envelope{e, "nonce", 1000, ""};
  envelope.mac_hex = auth.sign(e, envelope.nonce, envelope.issued_ms);
  assert(auth.verify(envelope));
  envelope.event.source = "N02";
  assert(!auth.verify(envelope));

  ReplayGuard guard(5000, 2);
  assert(guard.accept("N01", "same", 1000, 1100));
  assert(!guard.accept("N01", "same", 1000, 1100));
  assert(guard.accept("N02", "same", 1000, 1100));
  assert(!guard.accept("N03", "other", 1000, 1100));
  assert(guard.accept("N03", "other", 7000, 7000));
  return 0;
}
