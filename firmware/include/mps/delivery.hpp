#pragma once
#include <set>
#include <string>
namespace mps {
class DeliveryLedger{public: bool accept(const std::string&id){return seen_.insert(id).second;} private:std::set<std::string> seen_;};
}
