# Feature Traceability Matrix

| Requirement | Feature/contract | Implementation | Current evidence | Remaining gate |
|---|---|---|---|---|
| REQ-ARCH-001 | Ports/adapters | `ports.hpp`, `node_core.hpp` | host tests | target/HIL adapters |
| REQ-ARCH-002 | Event/state model | `event_bus.hpp`, `state_machine.hpp` | host tests | FreeRTOS/target timing |
| REQ-COMM-001 | durable-ACK-aware store/replay | `node_core.hpp`, `queue.hpp`, `types.hpp` | host/sim | persistent flash/gateway HIL |
| REQ-COMM-002/004 | duplicate/stale/gap handling | `delivery.hpp` | unit | transport HIL |
| REQ-COMM-003 | event identity/sequence/time/schema | `types.hpp` | contract review/tests | persistent sequence HIL |
| REQ-CFG-001 | transactional config + rollback | `config.hpp` | unit | NVS HIL |
| REQ-NET-001 | make-before-break profile model | `wireless.hpp` | unit | real AP/credential HIL |
| REQ-NET-002 | local-first operation | `node_core.hpp`, `ccoc.hpp` | host/sim | HIL |
| REQ-OTA-001 | staged OTA model/rollback | `ota.hpp` | unit | ESP-IDF A/B/brownout HIL |
| REQ-OTA-002 | coverage policy | `coverage.hpp` + architecture | unit | fleet/HIL/field |
| REQ-OTA-003 | gateway-relay contract | architecture/OTA sequence | design verified | local-radio HIL |
| REQ-SEC-001 | RBAC/audited idempotent commands | `security.hpp`, `command.hpp` | unit | persistent audit/HIL |
| REQ-SEC-002 | authenticated envelope/replay | `auth.hpp`, `host_auth.*` | HMAC unit | ESP-IDF crypto/key HIL |
| REQ-COV-001 | coverage interlock | `coverage.hpp` | unit | measured field coverage |
| REQ-FUS-001/002 | fusion dedup/validation | `sensor_fusion.hpp` | unit | sensor field accuracy |
| REQ-PWR-001 | power policy | `power.hpp` | unit | battery/brownout HIL |
| REQ-CCOC-001 | perimeter health separate from Internet | `ccoc.hpp` | unit | CCOC integration HIL |
| REQ-CCOC-002 | operations surface | CCOC architecture | partial design | API/UI/HIL |
| REQ-REL-001/002 | fail-soft/degraded behavior | state/coverage/CCOC models | unit/sim | HIL/field |
| REQ-VV-001 | physical authorization gate | V&V/completion docs | review | HIL+field |
