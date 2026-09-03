# System Requirements Specification

| Document ID | MPS-SYS-REQ-001 |
|---|---|
| Version | 1.1 |
| Status | BASELINED |

`Verification`: UT=unit, CT=contract, IT=integration, SIM=simulation, HIL=hardware-in-loop, FIELD=field.

| ID | Requirement | Verification |
|---|---|---|
| REQ-ARCH-001 | Core domain logic **shall** depend on stable ports/contracts rather than concrete sensors, radios, storage or external services. | CT/IT |
| REQ-ARCH-002 | Node behavior **shall** be event-driven and governed by explicit state machines for operational lifecycle transitions. | UT/HIL |
| REQ-COMM-001 | A P0/P1 event that has received a durable-local acknowledgement **shall** survive upstream Internet outage and be eligible for replay. | IT/SIM/HIL |
| REQ-COMM-002 | Delivery **shall** tolerate retries without duplicate event/incident processing. | UT/IT/HIL |
| REQ-COMM-003 | Critical events **shall** preserve globally unique event identity, source, monotonically increasing source sequence, original occurrence time, priority and schema version. | CT/HIL |
| REQ-COMM-004 | Replay processing **shall** detect duplicate, stale and sequence-gap conditions. | UT/IT |
| REQ-CFG-001 | Critical configuration changes **shall** support stage/test/commit and rollback to a last-known-good configuration. | UT/HIL |
| REQ-NET-001 | Wireless credential/AP migration **shall** use make-before-break where technically feasible and shall not revoke the last-known-good profile before the candidate is verified against a trusted gateway. | UT/HIL |
| REQ-NET-002 | Loss of Internet **shall not** by itself stop local sensing, local event buffering/correlation or local CCOC status. | IT/SIM/HIL |
| REQ-OTA-001 | OTA **shall** validate authenticity/compatibility, use an inactive candidate image/slot, perform post-boot self-test, and support rollback. | UT/HIL |
| REQ-OTA-002 | Fleet rollout **shall** support canary/staged deployment and prevent planned simultaneous disruption that would violate minimum coverage policy. | SIM/HIL/FIELD |
| REQ-OTA-003 | OTA transport **shall not** require direct Wi-Fi on every child node; a gateway-relayed local transport may distribute signed chunks. | CT/HIL |
| REQ-SEC-001 | Privileged commands **shall** be default-deny, role-authorized, idempotent where required, and auditable. | UT/IT/HIL |
| REQ-SEC-002 | Authenticated message envelopes **shall** detect tampering and replay; host reference uses HMAC-SHA-256 and target implementation shall use an approved ESP-IDF cryptographic primitive/key-protection design. | UT/HIL |
| REQ-SEC-003 | Secrets/private keys/production credentials **shall not** be committed to the repository or logged in plaintext. | Review/HIL |
| REQ-COV-001 | Planned maintenance/update actions **shall** be blocked when projected coverage falls below configured minimum policy. | UT/SIM/FIELD |
| REQ-FUS-001 | Sensor fusion **shall** avoid treating repeated observations from the same sensor type as independent corroboration. | UT/FIELD |
| REQ-FUS-002 | Invalid, stale or future-dated sensor observations **shall not** increase fusion confidence. | UT/FIELD |
| REQ-PWR-001 | Detection **shall** remain prioritized during backup/low/critical power while unsafe OTA/nonessential work is inhibited by policy. | UT/HIL |
| REQ-CCOC-001 | CCOC **shall** distinguish perimeter operational health from external Internet connectivity. | UT/IT/HIL |
| REQ-CCOC-002 | CCOC **shall** expose incidents, node/gateway health, coverage status, queue/backlog and audit-relevant command outcomes. | IT/HIL |
| REQ-REL-001 | The system **shall** fail soft: loss of a single noncritical component shall not silently disable the entire perimeter. | SIM/HIL/FIELD |
| REQ-REL-002 | The system **shall** report DEGRADED/FAULT truthfully when required capability is unavailable. | UT/HIL |
| REQ-VV-001 | Operational authorization **shall require** HIL and field evidence; host/simulation evidence alone is insufficient. | Review |
