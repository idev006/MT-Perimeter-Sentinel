#pragma once

namespace mps {

enum class Role { VIEWER, OPERATOR, ENGINEER, ADMIN, SECURITY_ADMIN };
enum class Action {
  VIEW_STATUS,
  ACK_INCIDENT,
  RUN_DIAGNOSTIC,
  SET_CONFIG,
  REBOOT_NODE,
  START_OTA,
  ROTATE_CREDENTIALS,
  MANAGE_SECURITY
};

inline bool authorized(Role role, Action action) {
  switch (action) {
    case Action::VIEW_STATUS:
      return true;
    case Action::ACK_INCIDENT:
      return role != Role::VIEWER;
    case Action::RUN_DIAGNOSTIC:
      return role == Role::ENGINEER || role == Role::ADMIN || role == Role::SECURITY_ADMIN;
    case Action::SET_CONFIG:
    case Action::REBOOT_NODE:
    case Action::START_OTA:
      return role == Role::ENGINEER || role == Role::ADMIN;
    case Action::ROTATE_CREDENTIALS:
    case Action::MANAGE_SECURITY:
      return role == Role::SECURITY_ADMIN || role == Role::ADMIN;
  }
  return false;
}

inline bool authorized(Role role, bool privileged) {
  return privileged ? authorized(role, Action::START_OTA) : authorized(role, Action::VIEW_STATUS);
}

}  // namespace mps
