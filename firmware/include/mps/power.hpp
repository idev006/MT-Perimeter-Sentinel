#pragma once

namespace mps {

enum class PowerState { NORMAL, BACKUP, LOW, CRITICAL, OFFLINE };

struct PowerPolicy {
  static bool allow_detection(PowerState state) { return state != PowerState::OFFLINE; }
  static bool allow_ota(PowerState state) { return state == PowerState::NORMAL; }
  static bool allow_nonessential_work(PowerState state) {
    return state == PowerState::NORMAL || state == PowerState::BACKUP;
  }
};

}  // namespace mps
