# Verification Test Specification

| Field | Value |
|---|---|
| Document ID | MPS-VV-TEST-001 |
| Version | 1.1 |
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

## Reliability field test families
| Test family | Purpose |
|---|---|
| T-FIELD-SENSE | Measure human intrusion detection effectiveness against the approved scenario set; target >=80% before expansion. |
| T-FIELD-FALSE | Measure nuisance/false alarms during no-human operation; classify source and confirm no sustained alarm behavior. |
| T-FIELD-SUN | Direct sun and thermal-transition susceptibility. |
| T-FIELD-WIND | Wind and bamboo-pole/sensor-head movement susceptibility. |
| T-FIELD-RAIN | Rain/wet/humidity behavior and ingress/reset susceptibility. |
| T-FIELD-ANIMAL | Common small-animal/insect nuisance-trigger behavior where practical. |
| T-FIELD-ENV | Birdhouse outer weather shield, sealed electronics enclosure, temperature/humidity/condensation evidence. |
| T-FIELD-RF | Link margin/interference/reconnect behavior. |
| T-FIELD-COV | Three-side coverage, overlap and direction/path behavior; later full-perimeter coverage. |
| T-FIELD-PWR | Power draw/runtime/reset/brownout under day/night conditions. |
| T-FIELD-SOAK | 24h / 72h / 7d operation with false-alarm, event-loss, reboot and environment trend evidence. |

## Confirmed-incident test rule
A test shall distinguish raw sensor observations, normalized events, suspicious/corroborated activity and confirmed incidents. A single noisy/isolated sensor observation shall not be counted as a successful confirmed alarm path unless the approved policy explicitly allows that scenario and evidence justifies it.

## Metrics
For each defined intrusion scenario:
`Detection effectiveness = detected valid attempts / total valid attempts × 100%`.

Record false alarms separately as confirmed incidents generated without a valid human intrusion stimulus. Raw sensor triggers that are correctly suppressed by fusion/correlation are diagnostic evidence, not false confirmed incidents.

## Acceptance discipline
Each executed test records build/firmware/config version, topology, equipment/environment, steps, expected/actual result, evidence location and defect linkage. A defect affecting a mission/security requirement requires a regression test before closure.

Host evidence does not substitute for physical sensing reliability. Failure of the >=80% field gate or occurrence of sustained environment-driven confirmed alarms blocks pilot expansion.
