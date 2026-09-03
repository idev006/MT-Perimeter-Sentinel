#pragma once
namespace mps {
enum class NodeState { BOOTING, INITIALIZING, ACTIVE, DEGRADED, MAINTENANCE, FAULT };
enum class Signal { INIT_OK, CONNECTIVITY_LOST, CONNECTIVITY_RESTORED, ENTER_MAINTENANCE, EXIT_MAINTENANCE, FATAL_FAULT };
class NodeStateMachine {
 public:
  NodeState state() const { return state_; }
  void on(Signal s){
    if(s==Signal::FATAL_FAULT){state_=NodeState::FAULT;return;}
    switch(state_){
      case NodeState::BOOTING: if(s==Signal::INIT_OK) state_=NodeState::ACTIVE; break;
      case NodeState::INITIALIZING: break;
      case NodeState::ACTIVE: if(s==Signal::CONNECTIVITY_LOST) state_=NodeState::DEGRADED; else if(s==Signal::ENTER_MAINTENANCE) state_=NodeState::MAINTENANCE; break;
      case NodeState::DEGRADED: if(s==Signal::CONNECTIVITY_RESTORED) state_=NodeState::ACTIVE; break;
      case NodeState::MAINTENANCE: if(s==Signal::EXIT_MAINTENANCE) state_=NodeState::ACTIVE; break;
      case NodeState::FAULT: break;
    }
  }
 private: NodeState state_{NodeState::BOOTING};
};
}
