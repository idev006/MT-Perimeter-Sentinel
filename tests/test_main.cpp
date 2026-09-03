#include "mps/ccoc.hpp"
#include "mps/command.hpp"
#include "mps/config.hpp"
#include "mps/correlation.hpp"
#include "mps/coverage.hpp"
#include "mps/delivery.hpp"
#include "mps/event_bus.hpp"
#include "mps/host_auth.hpp"
#include "mps/node_core.hpp"
#include "mps/ota.hpp"
#include "mps/power.hpp"
#include "mps/queue.hpp"
#include "mps/security.hpp"
#include "mps/sensor_fusion.hpp"
#include "mps/state_machine.hpp"
#include "mps/wireless.hpp"

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace mps;

struct Tx final : ITransport {
  bool up{false};
  bool durable_ack{true};
  std::vector<Event> sent;
  bool available() const override { return up; }
  SendResult send(const Event& event) override {
    if (!up) return {false, DeliveryState::FAILED};
    sent.push_back(event);
    return {true, durable_ack ? DeliveryState::DURABLE_LOCAL : DeliveryState::RECEIVED_LOCAL};
  }
};

int main() {
  { NodeStateMachine sm; assert(sm.state()==NodeState::BOOTING); sm.on(Signal::BOOT_COMPLETE); assert(sm.state()==NodeState::INITIALIZING); sm.on(Signal::INIT_OK); assert(sm.state()==NodeState::ACTIVE); sm.on(Signal::CONNECTIVITY_LOST); assert(sm.state()==NodeState::DEGRADED); sm.on(Signal::CONNECTIVITY_RESTORED); assert(sm.state()==NodeState::ACTIVE); }
  { int count=0; EventBus bus; bus.subscribe([&](const Event&){++count;}); assert(bus.subscriber_count()==1); bus.publish(Event{}); assert(count==1); }
  { Tx tx; BoundedQueue queue(2); NodeCore core(tx,queue); Event event{"e1","N01",1,Priority::P0,"INTRUSION",1,1}; assert(core.submit(event)); assert(queue.size()==1); tx.up=true; assert(core.replay()==1); assert(queue.size()==0); }
  { Tx tx; tx.up=true; tx.durable_ack=false; BoundedQueue queue(2); NodeCore core(tx,queue); Event event{"e2","N01",2,Priority::P0,"INTRUSION",2,1}; assert(core.submit(event)); assert(queue.size()==1); assert(core.replay()==0); assert(queue.size()==1); }
  { BoundedQueue queue(1); assert(queue.push(Event{"debug","N01",1,Priority::P4,"DEBUG",0,1})); assert(queue.push(Event{"critical","N01",2,Priority::P0,"INTRUSION",0,1})); auto event=queue.peek(); assert(event&&event->id=="critical"); assert(queue.pop()); assert(!queue.pop()); }
  { bool threw=false; try{BoundedQueue invalid(0);}catch(const std::invalid_argument&){threw=true;} assert(threw); }
  { TransactionalConfig cfg({1,"A"}); assert(!cfg.apply_candidate({2,"B"},false)); assert(cfg.active().version==1); assert(cfg.apply_candidate({2,"B"},true)); assert(cfg.active().version==2); assert(cfg.rollback()); assert(cfg.active().version==1); assert(!cfg.stage_candidate({1,"OLD"})); }
  { std::vector<Observation> observations{{"radar",.6,100},{"radar",.9,110},{"pir",.7,120},{"tof",1.0,0}}; const double confidence=SensorFusion::fuse(observations,130,50); assert(confidence>.79&&confidence<.81); assert(SensorFusion::fuse({{"radar",2.0,120}},130,50)==0.0); assert(SensorFusion::fuse({{"radar",.9,140}},130,50)==0.0); }
  { assert(PowerPolicy::allow_detection(PowerState::CRITICAL)); assert(!PowerPolicy::allow_ota(PowerState::BACKUP)); assert(!PowerPolicy::allow_nonessential_work(PowerState::LOW)); }
  { Correlator ring16(RingTopology(16)); assert(ring16.direction({16,1,2})==Direction::CLOCKWISE); assert(ring16.direction({2,1,16})==Direction::COUNTER_CLOCKWISE); assert(ring16.direction({1,3})==Direction::UNKNOWN); assert(ring16.direction({1,2,1})==Direction::UNKNOWN); Correlator ring5(RingTopology(5)); assert(ring5.direction({5,1,2})==Direction::CLOCKWISE); }
  { DeliveryLedger ledger; assert(ledger.accept("evt-1")); assert(!ledger.accept("evt-1")); assert(ledger.observe("N01",1)==SequenceStatus::ACCEPTED); assert(ledger.observe("N01",3)==SequenceStatus::GAP); assert(ledger.observe("N01",2)==SequenceStatus::STALE); assert(ledger.observe("N01",3)==SequenceStatus::DUPLICATE); }
  { WirelessProfileManager wifi("A"); assert(!wifi.migrate("B",false)); assert(wifi.active()=="A"); assert(wifi.migrate("B",true)); assert(wifi.active()=="B"); assert(wifi.previous()&&*wifi.previous()=="A"); assert(wifi.revoke_previous()); }
  { SafeOta ota("1.0"); assert(!ota.install("2.0",false,true)); assert(ota.active()=="1.0"); assert(ota.install("2.0",true,true)); assert(ota.active()=="2.0"); assert(ota.state()==OtaState::COMMITTED); assert(ota.rollback()); assert(ota.active()=="1.0"); assert(!ota.stage("1.0",true,true)); }
  { assert(!CoveragePolicy::allow_disruptive_action(.60,.75)); assert(!CoveragePolicy::allow_disruptive_action(1.2,.75)); }
  { assert(authorized(Role::VIEWER,Action::VIEW_STATUS)); assert(!authorized(Role::VIEWER,Action::REBOOT_NODE)); assert(authorized(Role::ENGINEER,Action::REBOOT_NODE)); assert(!authorized(Role::ENGINEER,Action::ROTATE_CREDENTIALS)); assert(authorized(Role::SECURITY_ADMIN,Action::ROTATE_CREDENTIALS)); }
  { AuditedCommandService commands; assert(commands.execute("cmd-1","reboot:N01",Role::ENGINEER,Action::REBOOT_NODE)=="OK"); assert(commands.execute("cmd-1","reboot:N01",Role::ENGINEER,Action::REBOOT_NODE)=="OK"); assert(commands.audit().back().replayed); bool denied=false; try{commands.execute("cmd-2","reboot:N01",Role::VIEWER,Action::REBOOT_NODE);}catch(const std::runtime_error&){denied=true;} assert(denied); assert(commands.audit().back().result=="DENIED"); }
  { Event event{"auth-1","N01",7,Priority::P0,"INTRUSION",123,1}; OpenSslHmacSha256Authenticator auth("test-key-not-production"); AuthenticatedEnvelope envelope{event,"nonce-1",1000,""}; envelope.mac_hex=auth.sign(event,envelope.nonce,envelope.issued_ms); assert(auth.verify(envelope)); envelope.event.type="TAMPERED"; assert(!auth.verify(envelope)); ReplayGuard guard(5000); assert(guard.accept("nonce-a",1000,1200)); assert(!guard.accept("nonce-a",1000,1200)); assert(!guard.accept("old",1000,7001)); }
  { CcocStatus status{16,16,2,2,true,false,1.0}; assert(status.perimeter_health()==SystemHealth::OPERATIONAL); assert(status.external_connectivity()==ExternalConnectivity::OFFLINE); status.nodes_online=15; assert(status.perimeter_health()==SystemHealth::DEGRADED); status.local_engine_ok=false; assert(status.perimeter_health()==SystemHealth::FAULT); }
  std::cout<<"ALL_TESTS_PASS\n";
  return 0;
}
