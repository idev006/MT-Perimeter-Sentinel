# Software Supply-Chain Policy

| Field | Value |
|---|---|
| Document ID | MPS-SC-001 |
| Version | 1.0 |
| Status | BASELINED-PRE-HIL |

## Rules
- Prefer ESP-IDF/standard-library capabilities and minimize third-party dependencies on target firmware.
- Every external dependency/tool affecting a release shall have owner/source, version, license and security review recorded.
- CI dependencies/actions are version-controlled; unexpected dependency changes require review.
- Production signing/private keys and credentials are never committed to Git.
- Release artifacts shall be traceable to source commit, toolchain/configuration and verification evidence.
- Operational release shall produce an SBOM or equivalent dependency inventory and retain firmware hashes/signing metadata.
- Vulnerability fixes follow risk-based priority and must include regression/release evidence where relevant.

This policy is tailored to NIST SSDF secure-development practices; it is not a claim of formal certification.
