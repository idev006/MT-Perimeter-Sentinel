# Threat Model

| Field | Value |
|---|---|
| Document ID | MPS-SEC-TM-001 |
| Version | 1.0 |
| Status | BASELINED-PRE-HIL |

## Assets
Critical events/incidents, device identity and keys, configuration/credentials, firmware authenticity, command authority/audit, availability and truthful health/coverage state.

## Trust boundaries
Sensor/driver ↔ node core; child-node local radio ↔ gateway; gateway ↔ CCOC; CCOC ↔ external Internet services; maintainer/operator ↔ management interfaces; firmware artifact repository ↔ OTA consumer.

## Threats and treatments
| Threat | Example | Required treatment/evidence |
|---|---|---|
| Spoofing | fake node/event | device identity, authenticated envelope, target key provisioning |
| Tampering | modified event/firmware/config | MAC/signature/integrity verification; signed OTA |
| Replay | resend valid old alarm/command | nonce/freshness + sequence/idempotency windows |
| Information disclosure | leaked Wi-Fi/device secrets | secret-at-rest protection, no secrets in repo/log/audit |
| Denial of service | event flood/replay-cache exhaustion | bounded queues/caches, prioritization, pressure telemetry |
| Elevation of privilege | viewer invokes reboot/credential rotation | default-deny action RBAC and auditable commands |
| Supply-chain compromise | malicious dependency/firmware artifact | pinned/reviewed dependencies, trusted build/release, SBOM/signing policy |
| Physical compromise | node captured/reset | Secure Boot/Flash Encryption/key provisioning and tamper response are HIL/design controls |

## Residual risk
Host HMAC/RBAC tests prove reference behavior only. Production security posture is not accepted until ESP32 Secure Boot/Flash Encryption, protected key provisioning, target crypto and recovery behavior are verified.
