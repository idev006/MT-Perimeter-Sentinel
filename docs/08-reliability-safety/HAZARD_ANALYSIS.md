# Security-Function Hazard Analysis

| Field | Value |
|---|---|
| Document ID | MPS-HAZ-001 |
| Version | 1.0 |
| Status | BASELINED-PRE-HIL |

This is a project hazard analysis for security-function reliability; it is not a functional-safety certification.

| ID | Hazard | Effect | Controls / verification |
|---|---|---|---|
| H-001 | Critical event lost after sender believes delivery is durable | missed intrusion evidence | durable-local ACK semantics; restart/HIL persistence tests |
| H-002 | CCOC reports NORMAL while perimeter capability is impaired | operator false confidence | separate perimeter health/Internet status; coverage and node-health gates |
| H-003 | Excess false alarms | alarm fatigue / ignored genuine alarm | sensor fusion, field false-alarm measurements, tuning controls |
| H-004 | Missed detection / coverage gap | intrusion not detected | multi-node layout, M0 sensing validation, coverage field survey |
| H-005 | OTA/maintenance disables adjacent coverage | planned blind sector | coverage-aware staged/canary rollout, non-adjacent maintenance |
| H-006 | AP/password change locks out nodes | management/event path unavailable | make-before-break and last-known-good profile rollback |
| H-007 | power loss/brownout corrupts state | event/config loss or reboot loop | transactional storage, brownout/watchdog/HIL recovery tests |
| H-008 | privileged command compromised/replayed | unauthorized disruption | RBAC, authentication/replay guard, idempotency and audit |

## Rule
Any field/HIL finding that can silently reduce detection, evidence durability or truthful operator awareness is treated as a release blocker until corrected or explicitly accepted by the project owner with documented rationale.
