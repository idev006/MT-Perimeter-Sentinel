#pragma once

namespace mps {

enum class NodeState { BOOTING, INITIALIZING, ACTIVE, DEGRADED, MAINTENANCE, FAULT };
enum class Signal {
  BOOT_COMPLETE,
  INIT_OK,
  INIT_FAILED,
  CONNECTIVITY_LOST,
  CONNECTIVITY_RESTORED,
  ENTER_MAINTENANCE,
  EXIT_MAINTENANCE,
  FATAL_FAULT
};

class NodeStateMachine {
 public:
  NodeState state() const { return state_; }

  void on(Signal signal) {
    if (signal == Signal::FATAL_FAULT) {
      state_ = NodeState::FAULT;
      return;
    }

    switch (state_) {
      case NodeState::BOOTING:
        if (signal == Signal::BOOT_COMPLETE) state_ = NodeState::INITIALIZING;
        break;
      case NodeState::INITIALIZING:
        if (signal == Signal::INIT_OK) state_ = NodeState::ACTIVE;
        else if (signal == Signal::INIT_FAILED) state_ = NodeState::FAULT;
        break;
      case NodeState::ACTIVE:
        if (signal == Signal::CONNECTIVITY_LOST) state_ = NodeState::DEGRADED;
        else if (signal == Signal::ENTER_MAINTENANCE) state_ = NodeState::MAINTENANCE;
        break;
      case NodeState::DEGRADED:
        if (signal == Signal::CONNECTIVITY_RESTORED) state_ = NodeState::ACTIVE;
        else if (signal == Signal::ENTER_MAINTENANCE) state_ = NodeState::MAINTENANCE;
        break;
      case NodeState::MAINTENANCE:
        if (signal == Signal::EXIT_MAINTENANCE) state_ = NodeState::ACTIVE;
        break;
      case NodeState::FAULT:
        break;
    }
  }

 private:
  NodeState state_{NodeState::BOOTING};
};

}  // namespace mps
