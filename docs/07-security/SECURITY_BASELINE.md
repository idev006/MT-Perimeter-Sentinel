# Security Baseline

| Document ID | MPS-SEC-001 |
|---|---|
| Version | 1.1 |
| Status | BASELINED |

## Security objectives
Protect device identity, command authority, firmware authenticity, configuration integrity, event integrity, secrets and auditability without making cloud/Internet a dependency of local detection.

## Baseline controls
- default-deny role-based command authorization;
- idempotent command IDs and collision rejection;
- command/audit trail for privileged actions;
- authenticated message envelope and replay/freshness protection;
- signed firmware and target Secure Boot/Flash Encryption;
- credential rotation/revocation and make-before-break network migration;
- production secrets stored outside source control and protected at rest;
- device identity distinct from logical node identity so spare hardware can be securely reprovisioned;
- fail closed on signature/authentication failure.

## Host vs target cryptography
Host reference uses HMAC-SHA-256 via OpenSSL to verify canonical envelope behavior. ESP32 target shall use ESP-IDF-supported cryptography/key storage (for example mbedTLS plus Secure Boot/Flash Encryption and protected provisioning). Host keys are test-only and are not production material.

## Threat cases to verify
Tampered event, replayed nonce, stolen/revoked credential, rogue AP with matching SSID, unauthorized command, firmware image substitution, configuration rollback attack, debug interface exposure, audit deletion/tamper attempt.
