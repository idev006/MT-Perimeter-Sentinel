# Verification Test Specification

| Field | Value |
|---|---|
| Document ID | MPS-VV-TEST-001 |
| Version | 1.0 |
| Status | BASELINED-PRE-HIL |

## Host executable suites
| Test ID | Area | Automated target |
|---|---|---|
| T-HOST-REG-001 | full domain regression | `mps_tests` |
| T-HOST-DEL-001 | durable ACK, queue pressure, replay/gap closure | `mps_test_delivery` |
| T-HOST-SEC-001 | RBAC, command audit/idempotency, HMAC, replay bounds | `mps_test_security` |
| T-HOST-LIFE-001 | state/config/wireless/OTA lifecycle and rollback | `mps_test_lifecycle` |
| T-HOST-SIM-001 | store-and-forward reference scenario | `mps_sim` |
| T-HOST-SAN-001 | memory/undefined-behavior gate | ASan/UBSan via `make verify-all` |

## HIL test families
T-HIL-BOOT: boot/reset/watchdog/brownout; T-HIL-STORE: flash persistence and monotonic sequence; T-HIL-NET: AP/Internet outage and migration; T-HIL-OTA: A/B update/self-test/rollback/relay; T-HIL-SEC: key provisioning/Secure Boot/Flash Encryption/auth; T-HIL-CMD: command/audit persistence and safety interlocks.

## Field test families
T-FIELD-SENSE: detection/false alarms; T-FIELD-RF: link margin/interference; T-FIELD-COV: coverage/path/direction; T-FIELD-PWR: runtime/backup; T-FIELD-ENV: enclosure/environment; T-FIELD-SOAK: 24 h / 72 h / 7 d operation.

## Acceptance discipline
Each executed test records build/firmware/config version, topology, equipment/environment, steps, expected/actual result, evidence location and defect linkage. A defect affecting a mission/security requirement requires a regression test before closure.
