# System Architecture Description

| Document ID | MPS-ARCH-001 |
|---|---|
| Version | 1.1 |
| Status | BASELINED |

## Architectural style
- Layered by responsibility.
- Ports & Adapters for replaceable hardware/services.
- Event-driven asynchronous communication plus explicit state machines.
- Composable LEGO-like blocks: stable connectors, lifecycle, health, config and contract tests.
- Local-first, fail-soft, store-and-forward.

## Node layers
1. **Application/use cases**: detection workflows and policy orchestration.
2. **Domain**: event model, state, fusion, power, coverage, correlation rules.
3. **Ports/contracts**: sensor, transport, event store, authentication, clock/config interfaces.
4. **Adapters/infrastructure**: ESP-IDF Wi-Fi/ESP-NOW or other radio, flash/NVS/file store, sensor drivers, cryptography.
5. **HAL/platform**: ESP32/ESP-IDF and board-specific resources.

Dependency direction is toward domain/contracts; domain logic does not depend on a concrete sensor/radio/database.

## Major deployable subsystems
- **Perimeter Node:** sensing, local fusion, event creation, bounded/durable buffering, health, power policy, config/OTA client.
- **Gateway/Uplink Node:** local-radio ingress, durable store-and-forward, child-node management and OTA relay, trusted-gateway authentication.
- **Local CCOC:** incident/read model, health/coverage/queue monitoring, RBAC command boundary, OTA/config orchestration and audit.
- **External integrations:** optional notifications/cloud APIs. They are not dependencies of local detection.

## Reliability boundary
A transport `send()` is not equivalent to durable delivery. Core may discard its local queued copy only after the adapter reports `DURABLE_LOCAL` or stronger acknowledgement. This prevents silent event loss when a receiver accepts bytes but has not persisted the event.

## Architecture constraints
- No hidden cross-component access; components communicate through contracts/events/commands.
- Configuration, firmware and secrets are separate artifacts.
- No single AP/gateway/cloud dependency should disable the entire perimeter by design.
- Planned disruptive actions are subject to coverage and power safety policy.
- Internet status is separate from local perimeter health.
