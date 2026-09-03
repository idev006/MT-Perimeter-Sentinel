#include "mps/node_core.hpp"
#include "mps/queue.hpp"
#include <iostream>
#include <vector>

using namespace mps;

struct GatewayTransport final : ITransport {
  bool up{false};
  std::vector<Event> delivered;
  bool available() const override { return up; }
  SendResult send(const Event& event) override {
    if (!up) return {false, DeliveryState::FAILED};
    delivered.push_back(event);
    return {true, DeliveryState::DURABLE_LOCAL};
  }
};

int main() {
  GatewayTransport transport;
  BoundedQueue queue(64);
  NodeCore node(transport, queue);
  for (int i=0;i<16;++i) {
    const auto sequence=static_cast<std::uint64_t>(i+1);
    if(!node.submit(Event{"evt"+std::to_string(i+1),"N"+std::to_string(i+1),sequence,Priority::P0,"INTRUSION",i,1})) return 1;
  }
  std::cout<<"pending_before="<<queue.size()<<'\n';
  transport.up=true;
  const auto replayed=node.replay();
  std::cout<<"replayed="<<replayed<<" pending_after="<<queue.size()<<" delivered="<<transport.delivered.size()<<'\n';
  return (queue.size()==0&&transport.delivered.size()==16)?0:1;
}
