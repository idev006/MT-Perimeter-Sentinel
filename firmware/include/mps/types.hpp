#pragma once
#include <cstdint>
#include <string>
namespace mps {
enum class Priority:int { P0=0,P1=1,P2=2,P3=3,P4=4 };
struct Event { std::string id; std::string source; std::uint64_t sequence{}; Priority priority{Priority::P2}; std::string type; std::int64_t occurred_ms{}; };
}
