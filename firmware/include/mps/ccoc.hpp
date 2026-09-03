#pragma once
#include <cstddef>
namespace mps {
enum class SystemHealth{OPERATIONAL,DEGRADED,FAULT};
struct CcocStatus{std::size_t nodes_online{},nodes_total{}; bool internet{}; double coverage{}; SystemHealth health()const{if(nodes_online==0||coverage<=0.0)return SystemHealth::FAULT; if(nodes_online<nodes_total||!internet||coverage<0.95)return SystemHealth::DEGRADED;return SystemHealth::OPERATIONAL;}};
}
