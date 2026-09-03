# Configuration Management Plan

| Document ID | MPS-CM-001 |
|---|---|
| Version | 1.0 |
| Status | BASELINED |

## Configuration items
Firmware, bootloader/partition table, device hardware revision, logical node/site configuration, network profiles, cryptographic identities/credentials, CCOC/gateway software, test evidence and controlled documents are distinct CIs.

## Rules
- firmware/config/secrets are separate artifacts;
- production secrets are never stored in Git;
- configuration has revision/schema identifiers and last-known-good rollback;
- network credential migration is staged before old credentials are revoked;
- release commits/tags identify exact source/evidence baseline;
- frequent small coherent commits are required;
- CI evidence must correspond to the source commit being released.

## Release naming
Use semantic software versions and milestone tags where useful (`g0-*`, `m1-*`, `pre-hil-*`, `v1.0.0`). Operational `v1.0.0` cannot be tagged as accepted until M5 evidence is approved.
