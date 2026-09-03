#include "mps/delivery.hpp"
#include "mps/node_core.hpp"
#include "mps/queue.hpp"
#include <cassert>
#include <vector>
using namespace mps;
struct Tx final : ITransport {
  bool up{true}; bool durable{true}; std::vector<Event> sent;
  bool available() const override { return up; }
  SendResult send(const Event& e) override {
    if (!up) return {false, DeliveryState::FAILED};
    sent.push_back(e);
    return {true, durable ? DeliveryState::DURABLE_LOCAL : DeliveryState::RECEIVED_LOCAL};
  }
};
int main() {
  DeliveryLedger ledger(4);
  assert(ledger.observe("N01", 10) == SequenceStatus::ACCEPTED);
  assert(ledger.observe("N01", 12) == SequenceStatus::GAP);
  assert(ledger.pending_count("N01") == 1);
  assert(ledger.observe("N01", 11) == SequenceStatus::ACCEPTED);
  assert(ledger.contiguous_sequence("N01") == 12);
  assert(ledger.pending_count("N01") == 0);
  assert(ledger.observe("N01", 12) == SequenceStatus::STALE);

  BoundedQueue q(1);
  assert(q.push(Event{"low", "N01", 1, Priority::P4, "DEBUG", 1, 1}));
  assert(q.push(Event{"critical", "N01", 2, Priority::P0, "INTRUSION", 2, 1}));
  assert(q.evicted_count() == 1);
  assert(!q.push(Event{"low2", "N01", 3, Priority::P4, "DEBUG", 3, 1}));
  assert(q.rejected_count() == 1);

  Tx tx; tx.durable = false;
  BoundedQueue pending(2);
  NodeCore core(tx, pending);
  assert(core.submit(Event{"e", "N01", 4, Priority::P0, "INTRUSION", 4, 1}));
  assert(pending.size() == 1);
  assert(core.replay() == 0);
  tx.durable = true;
  assert(core.replay() == 1);
  assert(pending.size() == 0);
}
