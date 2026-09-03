# Feature Traceability Matrix

| Requirement | Feature/contract | Implementation | Current evidence | Remaining gate |
|---|---|---|---|---|
| REQ-ARCH-001 | Ports/adapters | `ports.hpp`, `node_core.hpp`; SDD/ADR-0001 | host contract/regression | target/HIL adapters |
| REQ-ARCH-002 | Event/state model | `event_bus.hpp`, `state_machine.hpp` | lifecycle/full tests | FreeRTOS/target timing |
| REQ-COMM-001 | durable-ACK-aware store/replay | `node_core.hpp`, `queue.hpp`, `types.hpp`; ADR-0002 | delivery/full/sim | persistent flash/gateway HIL |
| REQ-COMM-002/004/005 | duplicate/stale/gap handling and gap closure | `delivery.hpp` | delivery/full tests | transport/restart HIL |
| REQ-COMM-003 | event identity/sequence/time/schema | `types.hpp` | contract/full tests | persistent sequence HIL |
| REQ-CFG-001 | transactional config + rollback | `config.hpp` | lifecycle/full tests | NVS HIL |
| REQ-NET-001 | make-before-break profile model | `wireless.hpp` | lifecycle/full tests | real AP/credential HIL |
| REQ-NET-002 | local-first operation | `node_core.hpp`, `ccoc.hpp` | host/sim | HIL |
| REQ-OTA-001 | staged OTA model/rollback | `ota.hpp` | lifecycle/full tests | ESP-IDF A/B/brownout HIL |
| REQ-OTA-002 | coverage policy | `coverage.hpp` + architecture | full test | fleet/HIL/field |
| REQ-OTA-003 | gateway-relay contract | architecture/OTA sequence | design review | local-radio HIL |
| REQ-SEC-001 | RBAC/audited idempotent commands | `security.hpp`, `command.hpp` | security/full tests | persistent audit/HIL |
| REQ-SEC-002 | authenticated envelope/replay | `auth.hpp`, `host_auth.*` | security/full HMAC tests | ESP-IDF crypto/key HIL |
| REQ-SEC-003/004 | secret handling/no raw secret audit payload | coding standard, `command.hpp` | review/security tests | target logging review |
| REQ-RES-001 | bounded replay/queue pressure visibility | `auth.hpp`, `queue.hpp`, `delivery.hpp` | delivery/security/full tests | capacity/load HIL |
| REQ-COV-001 | coverage interlock | `coverage.hpp` | full test | measured field coverage |
| REQ-FUS-001/002 | fusion dedup/validation | `sensor_fusion.hpp` | full test | sensor field accuracy |
| REQ-PWR-001 | power policy | `power.hpp` | full test | battery/brownout HIL |
| REQ-CCOC-001 | perimeter health separate from Internet | `ccoc.hpp` | full test | CCOC integration HIL |
| REQ-CCOC-002 | operations surface | CCOC architecture | partial design | API/UI/HIL |
| REQ-REL-001/002 | fail-soft/degraded behavior | state/coverage/CCOC models; hazard analysis | unit/sim/review | HIL/field |
| REQ-VV-001 | physical authorization gate | V&V plan, test spec, completion matrix | review | HIL+field |
