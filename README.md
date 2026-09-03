# MT-Perimeter-Sentinel

Distributed, camera-free electronic perimeter intrusion-detection system for an initial ~20 m × 20 m site using approximately 16 cooperating sensing nodes.

## Project mission
Detect, correlate, record, and surface potential perimeter intrusion while remaining locally operational during Internet outages and degrading safely when nodes, gateways, power, wireless links, or external services fail.

## Current release state
**PRE-HIL SOFTWARE REFERENCE BASELINE. Operational deployment is not authorized.**

The repository contains C++20 domain/reference logic, an ESP-IDF target skeleton, host simulation, tests, CI, engineering documentation, traceability, and HIL/field acceptance plans. Physical sensing accuracy, RF behavior, ESP32 flash/OTA/brownout behavior, power runtime, enclosure/environment performance, and full site coverage require HIL/field evidence.

## Architecture
Layered + Ports/Adapters + Event-Driven + Composable Blocks ("rail/plug" and LEGO-like composition).

Core blocks: Sensor adapters → Sensor fusion → Node core/event bus/state machine → durable event store → transport → gateway/store-and-forward → correlation/incident engine → local-first CCOC → external notifications/integrations.

## Build and verification
```bash
make verify-all
```
This runs strict-warning host build, unit/integration tests, reference simulation, and ASan/UBSan verification.

## Evidence levels
`UNIT → CONTRACT → INTEGRATION → SIMULATED → HOST_VERIFIED → VIRTUAL_TARGET → HIL → FIELD → OPERATIONAL_ACCEPTANCE`

## SSOT policy
GitHub `idev006/MT-Perimeter-Sentinel` is the durable project SSOT. Secrets, production credentials, and private keys must never be committed.

See `docs/09-verification-validation/PROJECT_COMPLETION_MATRIX.md` for current readiness and remaining gates.
