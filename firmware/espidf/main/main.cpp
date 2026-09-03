#include "mps/state_machine.hpp"
#include <cstdio>

extern "C" void app_main() {
  mps::NodeStateMachine state_machine;
  state_machine.on(mps::Signal::BOOT_COMPLETE);
  state_machine.on(mps::Signal::INIT_OK);
  if (state_machine.state() != mps::NodeState::ACTIVE) {
    std::printf("MPS_TARGET_BOOT_FAIL\n");
    return;
  }
  std::printf("MPS_TARGET_BOOT_OK\n");
}
