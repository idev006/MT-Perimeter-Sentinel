# Security-Function Hazard Analysis

| Field | Value |
|---|---|
| Document ID | MPS-HAZ-001 |
| Version | 1.1 |
| Status | BASELINED-PRE-HIL |

This is a project hazard analysis for security-function reliability; it is not a functional-safety certification.

| ID | Hazard | Effect | Controls / verification |
|---|---|---|---|
| H-001 | Critical event lost after sender believes delivery is durable | missed intrusion evidence | durable-local ACK semantics; restart/HIL persistence tests |
| H-002 | CCOC reports NORMAL while perimeter capability is impaired | operator false confidence | separate perimeter health/Internet status; coverage and node-health gates |
| H-003 | Excess false alarms | alarm fatigue / ignored genuine alarm | multi-sensor/node corroboration; field false-alarm and soak measurements; noisy-sensor suppression |
| H-004 | Missed detection / coverage gap | intrusion not detected | >=80% defined-scenario field gate; multi-node layout; M0 sensing validation; coverage survey |
| H-005 | OTA/maintenance disables adjacent coverage | planned blind sector | coverage-aware staged/canary rollout, non-adjacent maintenance |
| H-006 | AP/password change locks out nodes | management/event path unavailable | make-before-break and last-known-good profile rollback |
| H-007 | power loss/brownout corrupts state | event/config loss or reboot loop | transactional storage, brownout/watchdog/HIL recovery tests |
| H-008 | privileged command compromised/replayed | unauthorized disruption | RBAC, authentication/replay guard, idempotency and audit |
| H-009 | Direct sun/thermal transition causes repeated sensor trigger | sustained nuisance alarm / alarm fatigue | environmental scenario testing; cross-sensor/node confirmation; sensor derating/tuning |
| H-010 | Wind causes bamboo pole or sensor head movement | radar/motion false detections | rigid internal sensor bracket, mechanical tolerance test, windy-day field run |
| H-011 | Rain/condensation/humidity affects electronics or sensing | false alarms, resets, corrosion or missed detection | sealed inner enclosure, protected vents/windows, temperature/humidity telemetry, inspection/soak |
| H-012 | Insects/birds/small animals occupy or pass sensor housing | nuisance alarms, blockage, wiring damage | animal-resistant weather shield, protected openings, field false-alarm classification |
| H-013 | Solar heating causes enclosure over-temperature | resets, shortened component life, sensor drift | shaded/double-roof weather shield, air gap, measured enclosure temperature, thermal gate |
| H-014 | Low-cost deployment spreads budget too thin | unreliable sensors/enclosures and poor maintainability | staged 3-side pilot, evidence-gated expansion, reliability takes priority over node count |

## Rule
Any field/HIL finding that can silently reduce detection, evidence durability or truthful operator awareness is treated as a release blocker until corrected or explicitly accepted by the project owner with documented rationale.

Failure to meet the defined >=80% detection gate or occurrence of sustained environment-driven confirmed alarms blocks expansion to the next deployment stage.
