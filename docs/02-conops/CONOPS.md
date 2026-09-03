# Concept of Operations (CONOPS)

| Document ID | MPS-CONOPS-001 |
|---|---|
| Version | 1.0 |
| Status | BASELINED |

## Operational context
The system protects an approximately 20 m × 20 m perimeter without cameras. The baseline topology uses four corner nodes and intermediate nodes for about 16 distributed sensing points. Some nodes may be child nodes with no direct Wi-Fi/Internet connection; they communicate through a local transport to gateway/uplink nodes.

## Actors
- **Operator:** monitors incidents, acknowledges/investigates/resolves.
- **Engineer:** diagnostics, configuration and maintenance operations.
- **Administrator/Security Administrator:** fleet OTA, credentials, security policy.
- **Node:** local sensing, buffering, health and recovery.
- **Gateway:** durable ingress/store-and-forward, relay management/OTA and upstream connectivity.
- **CCOC:** local command/control and situational awareness.
- **External service:** optional notifications/cloud integrations.

## Primary operating modes
- NORMAL: required local capabilities available.
- DEGRADED: one or more capabilities impaired but perimeter still partially operational.
- MAINTENANCE: intentional controlled service reduction.
- FAULT: required local capability unavailable.
- RECOVERY: controlled restoration/reconciliation following fault/outage.

## Representative mission scenario
1. N04 detects motion evidence; N05 and N06 corroborate within the correlation window.
2. Local logic creates normalized events with unique IDs, occurrence times and sequences.
3. Gateway durably accepts events and local correlation creates an incident/path estimate.
4. CCOC presents incident, node/coverage health, and local system status.
5. If Internet is down, external notifications queue while local incident handling continues.
6. When Internet returns, queued external messages replay with idempotent processing; original occurrence times are preserved.

## Failure scenario
If a node or gateway fails, the system reports reduced coverage/capability rather than falsely reporting NORMAL. Critical events already durably acknowledged must survive restart/outage according to the applicable storage contract.

## Maintenance scenario
New firmware/configuration is staged, verified, applied to non-adjacent/canary nodes first, self-tested, and committed only after health checks. A failed candidate rolls back. Child nodes may receive signed firmware chunks through a gateway/local-radio relay.
