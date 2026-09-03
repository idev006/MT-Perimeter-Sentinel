# HIL and Field Acceptance Plan

| Document ID | MPS-VV-HIL-001 |
|---|---|
| Version | 1.1 |
| Status | BASELINED |

Progression: **single node → 3-node cluster → one-side ~20 m pilot → ~16-node perimeter → soak/operational acceptance**.

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
| ID | Test | Evidence |
|---|---|---|
| FIELD-SENSE-001 | human crossing at representative positions/speeds | detection rate/confidence |
| FIELD-FALSE-001 | no-human environmental run | false alarms/day |
| FIELD-RF-001 | all-node RF/link survey | RSSI/loss/latency/reconnect map |
| FIELD-COV-001 | one-side and full perimeter traversal | coverage gaps/direction accuracy |
| FIELD-PWR-001 | measured runtime/consumption | power budget/runtime |
| FIELD-ENV-001 | heat/rain/humidity/enclosure inspection | environmental evidence |
| FIELD-SOAK-024/072/168 | 24h/72h/7d soak | uptime, reboots, queue, false alarms, event loss |

Operational release requires review of evidence, unresolved risk acceptance, runbooks and rollback readiness.
