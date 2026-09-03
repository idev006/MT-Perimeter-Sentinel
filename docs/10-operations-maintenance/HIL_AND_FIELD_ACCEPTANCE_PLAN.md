# HIL and Field Acceptance Plan

| Document ID | MPS-VV-HIL-001 |
|---|---|
| Version | 1.2 |
| Status | BASELINED |

Progression: **single node → 3-node cluster → three-side reliability pilot → full perimeter candidate → soak/operational acceptance**.

The first outdoor deployment is intentionally staged. Exact node count/spacing is evidence-driven; the current planning range for the three-side pilot is approximately 10-13 nodes, subject to M0 sensing/coverage measurements and the THB 5,000 project budget constraint.

## HIL test catalog
| ID | Test | Minimum acceptance |
|---|---|---|
| HIL-BOOT-001 | cold boot/reset/watchdog | returns to expected state; reason observable |
| HIL-QUEUE-001 | critical event + reboot/outage | durably acknowledged event recovered, no silent loss |
| HIL-NET-001 | Internet loss | local sensing/CCOC continue; external backlog visible |
| HIL-NET-002 | AP/profile migration | new profile verified before old revoked; rollback works |
| HIL-OTA-001 | valid OTA | candidate verifies, boots, self-tests, commits |
| HIL-OTA-002 | corrupt/unsigned candidate | rejected fail-closed |
| HIL-OTA-003 | interruption/brownout | previous valid image recoverable |
| HIL-OTA-004 | child relay OTA | missing chunks retransmit; final image verifies on child |
| HIL-PWR-001 | mains loss/backup/low power | detection prioritized; OTA inhibited per policy |
| HIL-SEC-001 | replay/tampered message | rejected and observable |
| HIL-CMD-001 | unauthorized/duplicate command | denied/idempotent and audited |
| HIL-STOR-001 | queue pressure/restart | priority policy and persistence verified |

## Field test catalog
| ID | Test | Minimum acceptance / evidence |
|---|---|---|
| FIELD-SENSE-001 | human approach/crossing/leaving at representative positions, directions and speeds | >=80% detection effectiveness across the defined scenario set before pilot expansion |
| FIELD-FALSE-001 | no-human environmental run | no sustained confirmed-intrusion alarm; false alarms/day recorded and classified |
| FIELD-SUN-001 | direct sun and morning/noon/evening thermal transitions | no sustained confirmed alarm; enclosure and sensor temperature logged |
| FIELD-WIND-001 | windy conditions / controlled pole movement within installation tolerance | no sustained confirmed alarm; pole movement and event stream recorded |
| FIELD-RAIN-001 | rain/wet/humidity condition | no unsafe ingress/reset/sustained confirmed alarm; inspection evidence |
| FIELD-ANIMAL-001 | common small animal/insect exposure where practical | nuisance triggers classified; isolated trigger shall not become confirmed incident |
| FIELD-ENV-001 | birdhouse-style weather shield + sealed inner electronics enclosure | enclosure temperature/humidity, condensation evidence, ingress/insect inspection |
| FIELD-RF-001 | all-node RF/link survey | RSSI/loss/latency/reconnect map |
| FIELD-COV-001 | three-side traversal then full perimeter traversal | coverage gaps/direction accuracy |
| FIELD-PWR-001 | measured runtime/consumption under day/night temperatures | power budget/runtime; reset/brownout count |
| FIELD-SOAK-024/072/168 | 24h/72h/7d soak | uptime, reboots, queue, false alarms, event loss and temperature/humidity trends |

## Defined sensing scenario set
At minimum include: walking approach, perpendicular crossing, diagonal crossing, walking parallel to boundary, leaving, running, slow/low-profile movement where safe, repeated traversal near node overlap, and traversal near corner geometry. Each scenario records attempts, detections, misses, confidence, node/sensor evidence and environment.

## Reliability gate
Do not expand from the three-side pilot to a full perimeter merely because devices remain online. Expansion requires:
1. FIELD-SENSE-001 >=80% detection effectiveness for the approved scenario set;
2. no sustained environment-driven confirmed alarm in the environmental tests;
3. no unexplained critical-event loss;
4. no hidden coverage/health degradation;
5. acceptable mounting/enclosure/power behavior.

If the gate fails, adjust sensor selection/placement, mechanical mounting, environmental protection, fusion/correlation policy or node spacing and repeat the evidence cycle.

Operational release requires review of evidence, unresolved risk acceptance, runbooks and rollback readiness.
