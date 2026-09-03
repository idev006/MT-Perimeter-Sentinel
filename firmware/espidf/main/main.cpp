#include "mps/state_machine.hpp"
#include <cstdio>
extern "C" void app_main(){mps::NodeStateMachine sm;sm.on(mps::Signal::INIT_OK);std::printf("MPS_TARGET_BOOT_OK\n");}
