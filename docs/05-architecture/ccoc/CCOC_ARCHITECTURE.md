# CCOC Architecture

| Document ID | MPS-ARCH-CCOC-001 |
|---|---|
| Version | 1.0 |
| Status | BASELINED |

## Purpose
Provide local-first situational awareness and command/control. CCOC is not merely a dashboard; it is an operational subsystem.

## Required views/capabilities
- perimeter health and actual coverage state;
- node/gateway/AP/power health;
- active incidents and timeline;
- local/upstream queue backlog and oldest pending critical event;
- Internet/external integration status shown separately from perimeter health;
- firmware/config version drift and rollout state;
- RBAC-protected commands and audit outcomes.

## Command flow
`User → AuthN/AuthZ → Safety interlock (coverage/power/state) → Command journal/idempotency → Gateway/Node → Result → Audit`

Unknown/high-impact commands are default-deny. CCOC shall not bypass component contracts to modify node internals.
