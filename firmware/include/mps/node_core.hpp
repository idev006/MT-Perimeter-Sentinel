#pragma once
#include "ports.hpp"
namespace mps {
class NodeCore {
 public:
  NodeCore(ITransport& t,IEventStore& q):tx_(t),queue_(q){}
  bool submit(const Event& e){ if(tx_.available() && tx_.send(e)) return true; return queue_.push(e); }
  std::size_t replay(){ std::size_t sent=0; while(tx_.available()){auto e=queue_.pop(); if(!e) break; if(!tx_.send(*e)){queue_.push(*e);break;} ++sent;} return sent; }
 private:ITransport& tx_;IEventStore& queue_;
};
}
