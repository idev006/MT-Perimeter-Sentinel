# Documentation Standard

| Field | Value |
|---|---|
| Document ID | MPS-GOV-DOC-001 |
| Version | 1.0 |
| Status | BASELINED |
| Owner | Systems Engineering |
| SSOT | GitHub repository |

## Purpose
Define controlled-document rules for MT-Perimeter-Sentinel. Guidance basis includes ISO/IEC/IEEE 15288 systems life cycle practices, ISO/IEC/IEEE 29148 requirements engineering, ISO/IEC/IEEE 42010 architecture description, ISO 31000 risk management, ISO/IEC/IEEE 29119 testing concepts, and NIST resilience/security practices.

## Mandatory rules
1. Repository content is the project record; chat is not an authoritative project record.
2. Controlled engineering documents state purpose, scope, owner, version/status, assumptions, affected requirements/interfaces, verification implications, and change history when material.
3. Requirements use unique IDs and normative **shall** statements. Each safety/security/mission requirement has an identified verification method.
4. Architecture decisions that materially constrain implementations are recorded as architecture documents/ADRs before or with the code change.
5. Diagrams describe real contracts and behavior. Decorative diagrams are not evidence.
6. Implementation must conform to the approved baseline. If code reveals a better design, update the design/ADR and traceability rather than silently diverging.
7. Evidence classifications must not be overstated. Host/simulation evidence cannot close RF, sensing, environmental, power, flash, or physical-security acceptance.
8. Secrets and credentials are never committed.

## Document lifecycle
`DRAFT → IN_REVIEW → APPROVED → BASELINED → SUPERSEDED`

## Change control
Routine implementation/document corrections may proceed autonomously with coherent commits. Escalation is required for mission/scope change, major security posture change, irreversible architecture lock-in, significant procurement/budget, or explicit risk acceptance.
