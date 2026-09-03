#pragma once
#include <cstddef>

namespace mps {

enum class SystemHealth { OPERATIONAL, DEGRADED, FAULT };
enum class ExternalConnectivity { ONLINE, OFFLINE };

struct CcocStatus {
  std::size_t nodes_online{};
  std::size_t nodes_total{};
  std::size_t gateways_online{1};
  std::size_t gateways_total{1};
  bool local_engine_ok{true};
  bool internet{};
  double coverage{};

  SystemHealth perimeter_health() const {
    if (!local_engine_ok || nodes_total == 0 || nodes_online == 0 || gateways_online == 0 || coverage <= 0.0)
      return SystemHealth::FAULT;
    if (nodes_online < nodes_total || gateways_online < gateways_total || coverage < 0.95)
      return SystemHealth::DEGRADED;
    return SystemHealth::OPERATIONAL;
  }

  SystemHealth health() const { return perimeter_health(); }
  ExternalConnectivity external_connectivity() const {
    return internet ? ExternalConnectivity::ONLINE : ExternalConnectivity::OFFLINE;
  }
};

}  // namespace mps
