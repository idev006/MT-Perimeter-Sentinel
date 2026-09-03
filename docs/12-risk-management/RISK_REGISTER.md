# Risk Register

| Document ID | MPS-RISK-001 |
|---|---|
| Version | 1.0 |
| Status | ACTIVE |

Scale: Probability (P) 1-5, Impact (I) 1-5, Score=P×I. Scores 15-25 HIGH, 8-14 MEDIUM, 1-7 LOW.

| ID | Risk | P | I | Score | Treatment / gate |
|---|---|---:|---:|---:|---|
| R-001 | sensing technology cannot achieve acceptable detection/false-alarm behavior | 4 | 5 | 20 | M0/M3 field experiments; multi-sensor fusion |
| R-002 | RF gaps/interference cause unobserved event delivery failure | 4 | 5 | 20 | RF survey, local buffering, redundant uplinks/paths |
| R-003 | power outage/battery depletion disables perimeter | 3 | 5 | 15 | backup design, health telemetry, power policy, runtime tests |
| R-004 | OTA failure bricks/disables adjacent nodes | 3 | 5 | 15 | A/B rollback, signed candidate, staged non-adjacent rollout |
| R-005 | credential/AP change locks out fleet | 3 | 5 | 15 | make-before-break, trusted-gateway test, recovery provisioning |
| R-006 | critical events lost during outage/restart | 3 | 5 | 15 | durable ACK semantics, persistent stores, replay/idempotency HIL |
| R-007 | security credential/command compromise | 3 | 5 | 15 | RBAC, authenticated envelopes, Secure Boot/encryption, rotation/revocation |
| R-008 | environmental enclosure failure/water/heat/insects | 3 | 4 | 12 | enclosure design + field/environment inspection |
| R-009 | documentation/implementation/evidence drift | 3 | 4 | 12 | GitHub SSOT, traceability audit, CI/release manifest |
| R-010 | reconstructed baseline omits previously intended feature | 3 | 4 | 12 | independent audit, gap tracking, HIL acceptance |
