# Architecture Viewpoints

| Field | Value |
|---|---|
| Document ID | MPS-ARCH-VP-001 |
| Version | 1.0 |
| Status | BASELINED |

## Purpose
Provide a tailored architecture-description structure consistent with ISO/IEC/IEEE 42010 concepts: stakeholder concerns are addressed through explicit viewpoints and corresponding views.

## Viewpoints
| Viewpoint | Primary concerns | Current views/artifacts |
|---|---|---|
| Context | mission, actors, boundary, external dependencies | CONOPS; stakeholder/system context |
| Functional/component | responsibilities, composition, replaceability | ARCHITECTURE; SYSTEM_COMPONENT_DIAGRAM |
| Information/interface | event/command/config/telemetry contracts and semantics | COMMUNICATION_AND_MESSAGE_MODEL; ports/types |
| Runtime | asynchronous behavior, lifecycle, retry/recovery | NODE_STATE_MACHINE; STORE_FORWARD_SEQUENCE |
| Deployment | node/gateway/CCOC/Internet allocation | ARCHITECTURE; HIL/field plan; target skeleton |
| Security | trust boundaries, identity, authorization, integrity | SECURITY_BASELINE; THREAT_MODEL |
| Reliability/security-function | degraded modes, coverage, recovery, hazards | FAILURE_MODES; HAZARD_ANALYSIS |
| Verification | requirement-to-test-to-evidence | V&V plan; TEST_SPECIFICATION; traceability matrix |

## Architecture invariants
1. Local sensing and local incident handling do not require Internet availability.
2. Replaceable implementations connect through stable ports/contracts; no hidden cross-component wiring.
3. A critical event is not removed from sender durable backlog merely because bytes were received; at least durable-local acknowledgement is required.
4. Long-running embedded resources are bounded or explicitly governed by a retention policy.
5. Maintenance/OTA/configuration changes use stage/verify/commit/rollback where failure can impair mission capability.
6. External connectivity status and perimeter operational health are separate concerns.
7. Host/reference evidence cannot close physical RF, sensing, power, environmental, flash or target-security gates.
