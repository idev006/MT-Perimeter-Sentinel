# Failure Modes and Degraded Operation

| Document ID | MPS-REL-FMEA-001 |
|---|---|
| Version | 1.0 |
| Status | BASELINED |

This project protects property/life-related security operations, but this document is not a functional-safety certification.

| Failure mode | Expected behavior | Evidence now | Physical gate |
|---|---|---|---|
| Internet outage | Local detection/correlation/CCOC continue; outbound queue accumulates then replays | host/sim | HIL |
| AP/profile failure | Keep last-known-good profile; candidate must reach trusted gateway before commit | host model | AP HIL |
| Gateway unavailable | Child node buffers according to capacity/priority; system reports degraded path | host model | radio HIL |
| Node failure | Coverage reduced and surfaced; neighbor evidence may maintain partial capability | architecture | field |
| Adjacent node failures | More severe coverage degradation; disruptive maintenance blocked if below minimum | model | field |
| Sensor spam/stuck | Fusion does not treat repeated same-type evidence as independent corroboration | unit | sensor field |
| Queue pressure | Higher-priority event can displace lower-priority entry; P0 rejection must be observable | unit | flash/load HIL |
| Power outage/brownout | detection prioritized while power exists; OTA inhibited; state restored/reconciled | policy model | brownout HIL |
| Bad configuration | candidate rejected or rolled back; last-known-good remains | unit | NVS HIL |
| Failed OTA | candidate not committed; previous image remains/rolls back | unit model | partition/brownout HIL |
| Duplicate/replay | idempotent/replay guard rejects duplicate/stale input | unit | transport HIL |
| External notification outage | incident/event record remains authoritative; notification retried separately | architecture | integration |
| Reconnect storm | retry/backoff/throttling required at adapter/orchestrator layer | planned | HIL |

## Release blocker conditions
- unexplained P0/P1 event loss;
- system reports OPERATIONAL while required local capability is unavailable;
- update/config action can disconnect all management paths without rollback;
- retry creates duplicate incident/action;
- failed security verification falls open.
