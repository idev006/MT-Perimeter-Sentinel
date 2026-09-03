# Stakeholder Needs and System Context

| Field | Value |
|---|---|
| Document ID | MPS-STK-001 |
| Version | 1.0 |
| Status | BASELINED |
| Owner | Systems Engineering |

## Purpose
Capture stakeholder needs and the system boundary that drive system requirements. This document is intentionally solution-light; requirements and architecture refine these needs.

## Stakeholders and needs
| ID | Stakeholder | Need |
|---|---|---|
| STK-001 | Property owner/operator | Detect credible perimeter intrusion candidates without cameras and surface them promptly. |
| STK-002 | Operator | Maintain local situational awareness when Internet/cloud services are unavailable. |
| STK-003 | Operator | Know when coverage/capability is degraded; the system must not silently claim NORMAL. |
| STK-004 | Maintainer | Replace sensors/transports/storage implementations through stable interfaces and test components independently. |
| STK-005 | Maintainer | Update firmware/configuration safely with rollback and without intentionally creating large coverage gaps. |
| STK-006 | Security administrator | Authenticate devices/messages and authorize/audit privileged control actions. |
| STK-007 | Project owner | Develop iteratively, control cost/procurement by evidence gates, and preserve documents/source in GitHub SSOT. |

## System boundary
**Inside:** sensing nodes, node firmware, local transports, gateway functions, durable event handling, correlation/incident logic, local CCOC, configuration/OTA/security management interfaces.

**Outside:** mains utility, access points/routers, Internet providers, optional cloud/notification services, human response, physical site/environment, and external identity/notification providers.

External failure must be treated as an operating condition where practical, not assumed impossible.

## Key assumptions to verify
- Initial site is approximately 20 m x 20 m and baseline topology is about 16 nodes.
- At least some gateway/uplink nodes can join local Wi-Fi; child nodes need not join Wi-Fi directly.
- Selected sensing technology and RF topology remain subject to M0/HIL/field evidence.
- This project is a security-function system; it does not claim certified life-safety functionality.

## Need-to-requirement examples
STK-001 -> REQ-FUS-001 / field sensing acceptance.
STK-002 -> REQ-NET-002 / REQ-CCOC-001.
STK-003 -> REQ-CCOC-001 / REQ-COV-001.
STK-004 -> REQ-ARCH-001/002.
STK-005 -> REQ-CFG-001 / REQ-NET-001 / REQ-OTA-001..003.
STK-006 -> REQ-SEC-001..004.
