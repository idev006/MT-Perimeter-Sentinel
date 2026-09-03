#include "mps/config.hpp"
#include "mps/ota.hpp"
#include "mps/state_machine.hpp"
#include "mps/wireless.hpp"
#include <cassert>
using namespace mps;
int main() {
  NodeStateMachine sm;
  assert(sm.state()==NodeState::BOOTING);
  sm.on(Signal::BOOT_COMPLETE);
  assert(sm.state()==NodeState::INITIALIZING);
  sm.on(Signal::INIT_OK);
  assert(sm.state()==NodeState::ACTIVE);
  sm.on(Signal::ENTER_MAINTENANCE);
  assert(sm.state()==NodeState::MAINTENANCE);
  sm.on(Signal::EXIT_MAINTENANCE);
  assert(sm.state()==NodeState::ACTIVE);

  TransactionalConfig cfg({1,"A"});
  assert(!cfg.apply_candidate({2,"B"},false));
  assert(!cfg.candidate());
  assert(cfg.apply_candidate({2,"B"},true));
  assert(cfg.active().version==2);
  assert(cfg.rollback());
  assert(cfg.active().version==1);

  WirelessProfileManager wifi("A");
  assert(!wifi.migrate("B",false));
  assert(!wifi.candidate());
  assert(wifi.migrate("B",true));
  assert(wifi.active()=="B");
  assert(wifi.previous() && *wifi.previous()=="A");

  SafeOta ota("1.0");
  assert(!ota.stage("2.0",false,true));
  assert(ota.state()==OtaState::FAILED);
  assert(ota.stage("2.0",true,true));
  assert(!ota.boot_candidate(false));
  assert(ota.state()==OtaState::ROLLED_BACK);
  assert(ota.active()=="1.0");
  assert(ota.stage("2.0",true,true));
  assert(ota.boot_candidate(true));
  assert(ota.commit());
  assert(ota.active()=="2.0");
  assert(ota.rollback());
  assert(ota.active()=="1.0");
  return 0;
}
