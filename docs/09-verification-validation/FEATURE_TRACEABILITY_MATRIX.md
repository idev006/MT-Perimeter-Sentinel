# Feature Traceability Matrix

| Requirement | Feature | Implementation | Evidence | Remaining gate |
|---|---|---|---|---|
| REQ-ARCH-001 | Ports/Adapters | `ports.hpp`, `node_core.hpp` | host tests | HIL |
| REQ-ARCH-002 | Event/state model | `event_bus.hpp`, `state_machine.hpp` | host tests | target timing |
| REQ-COMM-001/2 | Queue/replay/idempotency | `queue.hpp`, `delivery.hpp` | host tests | flash/network HIL |
| REQ-CFG-001 | Transactional config | `config.hpp` | host tests | NVS HIL |
| REQ-NET-001 | Make-before-break Wi-Fi model | `wireless.hpp` | host tests | AP HIL |
| REQ-OTA-001 | Safe OTA model | `ota.hpp` | host tests | real partitions/brownout |
| REQ-SEC-001/2 | RBAC/audit/auth | `security.hpp`, `command.hpp` | host tests | secure boot/key HIL |
| REQ-COV-001 | Coverage interlock | `coverage.hpp` | host tests | field coverage |
| REQ-FUS-001 | Sensor fusion | `sensor_fusion.hpp` | host tests | sensor field accuracy |
| REQ-PWR-001 | Power policy | `power.hpp` | host tests | battery/brownout |
| REQ-CCOC-001 | Health/degraded model | `ccoc.hpp` | host tests | operational UI/HIL |
