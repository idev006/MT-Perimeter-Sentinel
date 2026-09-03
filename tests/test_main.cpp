#include "mps/ccoc.hpp"
#include "mps/command.hpp"
#include "mps/config.hpp"
#include "mps/correlation.hpp"
#include "mps/coverage.hpp"
#include "mps/delivery.hpp"
#include "mps/event_bus.hpp"
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
#include <vector>
using namespace mps;
struct Tx: ITransport{bool up=false;std::vector<Event> sent;bool available()const override{return up;}bool send(const Event&e)override{if(!up)return false;sent.push_back(e);return true;}};
int main(){
  {NodeStateMachine s; s.on(Signal::INIT_OK); assert(s.state()==NodeState::ACTIVE); s.on(Signal::CONNECTIVITY_LOST); assert(s.state()==NodeState::DEGRADED);}
  {int n=0; EventBus b; b.subscribe([&](const Event&){++n;}); b.publish(Event{}); assert(n==1);}
  {Tx tx; BoundedQueue q(2); NodeCore c(tx,q); Event e{"e1","N01",1,Priority::P0,"INTRUSION",1}; assert(c.submit(e)); assert(q.size()==1);tx.up=true;assert(c.replay()==1);assert(q.size()==0);}
  {BoundedQueue q(1); assert(q.push(Event{"d","N",1,Priority::P4,"DBG",0})); assert(q.push(Event{"c","N",2,Priority::P0,"CRIT",0})); auto e=q.pop(); assert(e&&e->id=="c");}
  {TransactionalConfig c({1,"A"}); assert(!c.apply_candidate({2,"B"},false)); assert(c.active().version==1); assert(c.apply_candidate({2,"B"},true));}
  {std::vector<Observation> o{{"radar",.9,100},{"radar",.8,110},{"pir",.7,120},{"tof",1.0,0}}; double x=SensorFusion::fuse(o,130,50); assert(x>.79&&x<.81);}
  {assert(PowerPolicy::allow_detection(PowerState::BACKUP));assert(!PowerPolicy::allow_ota(PowerState::BACKUP));}
  {Correlator c(RingTopology(16)); assert(c.direction({16,1,2})==Direction::CLOCKWISE);assert(c.direction({2,1,16})==Direction::COUNTER_CLOCKWISE);assert(c.direction({1,3})==Direction::UNKNOWN);}
  {DeliveryLedger l;assert(l.accept("x"));assert(!l.accept("x"));}
  {WirelessProfileManager w("A");assert(!w.migrate("B",false));assert(w.active()=="A");assert(w.migrate("B",true));}
  {SafeOta o("1.0");assert(!o.install("2.0",false,true));assert(o.install("2.0",true,true));assert(o.active()=="2.0");assert(o.rollback());}
  {assert(!CoveragePolicy::allow_disruptive_action(.60,.75));}
  {assert(!authorized(Role::VIEWER,true));assert(authorized(Role::ADMIN,true));}
  {CommandJournal j;assert(j.execute_once("c1","reboot")=="OK");assert(j.execute_once("c1","reboot")=="OK");bool threw=false;try{j.execute_once("c1","other");}catch(...){threw=true;}assert(threw);}
  {CcocStatus s{15,16,false,.94};assert(s.health()==SystemHealth::DEGRADED);}
  std::cout<<"ALL_TESTS_PASS\n";
}
