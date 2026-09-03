# Software Design Description

| Field | Value |
|---|---|
| Document ID | MPS-SDD-001 |
| Version | 1.0 |
| Status | BASELINED |

## Design style
C++ domain/reference software follows Layered + Ports/Adapters + Event-Driven + composable-block architecture. C is reserved for low-level ESP-IDF/vendor integration when appropriate.

## Major modules
| Module | Responsibility | Target allocation |
|---|---|---|
| types/ports | stable data and dependency contracts | node/gateway shared |
| state_machine/event_bus/node_core | node orchestration and lifecycle | ESP32 node |
| queue/delivery | bounded backlog, durable-delivery and replay semantics | node/gateway |
| sensor_fusion | corroboration without double-counting sensor type | node/gateway policy |
| topology/correlation/coverage | perimeter adjacency, direction, maintenance safety | gateway/CCOC |
| config/wireless/ota | transactional change and rollback models | node/fleet management |
| security/auth/command | RBAC, authenticated envelopes, replay and audit | node/gateway/CCOC |
| power/ccoc | degraded-power policy and situational status | node/CCOC |

## Embedded design rules
- No unbounded queue/cache on long-running node paths without an explicit retention policy.
- Blocking external operations are isolated behind ports/adapters.
- Failure states are explicit and observable; silent fallback that masks lost capability is prohibited.
- Priority can protect critical traffic, but eviction/rejection must be observable.
- Concrete ESP-IDF flash, Wi-Fi, radio, watchdog, OTA partition and crypto adapters remain target/HIL work until verified.

## Testability
Production adapters must have replaceable fakes/mocks or host-reference equivalents. Domain logic must compile/run on host without ESP32 hardware where technically practical.
