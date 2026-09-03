#pragma once
#include <string>
namespace mps {
struct Config { int version{}; std::string profile; };
class TransactionalConfig {
 public:
  explicit TransactionalConfig(Config active):active_(std::move(active)){}
  const Config& active() const{return active_;}
  bool apply_candidate(const Config& c,bool connectivity_ok){ if(!connectivity_ok) return false; active_=c; return true; }
 private:Config active_;
};
}
