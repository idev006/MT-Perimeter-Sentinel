# System Requirements

- REQ-ARCH-001: Core logic shall depend on stable ports, not concrete hardware/network/storage implementations.
- REQ-ARCH-002: Node behavior shall be event-driven with explicit state machines.
- REQ-COMM-001: Critical events shall survive Internet outage.
- REQ-COMM-002: Delivery shall tolerate retry without duplicate processing.
- REQ-COMM-003: Critical events shall preserve occurrence time and unique identity.
- REQ-CFG-001: Critical configuration changes shall support candidate/test/commit/rollback.
- REQ-NET-001: Wireless migration shall use make-before-break where feasible.
- REQ-OTA-001: OTA shall support signed/verified candidate, staged rollout, and rollback.
- REQ-SEC-001: Privileged commands shall be authorized and auditable.
- REQ-SEC-002: Authenticated message envelopes shall reject tampering/replay in the reference model.
- REQ-COV-001: Maintenance/update actions shall be blocked when projected coverage violates policy.
- REQ-FUS-001: Sensor-fusion policy shall avoid treating repeated evidence from one sensor type as independent corroboration.
- REQ-PWR-001: Detection shall remain prioritized during degraded power; unsafe OTA shall be inhibited.
- REQ-CCOC-001: CCOC shall distinguish NORMAL/DEGRADED/FAULT conditions and surface Internet-independent local status.
- REQ-VV-001: Operational authorization requires HIL and field evidence.
