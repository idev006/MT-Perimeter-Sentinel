# Engineering Process

| Document ID | MPS-GOV-PROC-001 |
|---|---|
| Version | 1.0 |
| Status | BASELINED |
| Process | Document-driven Agile Kanban + systems engineering |

## Lifecycle
`Need → Requirement → Architecture/ADR → Component/Interface → Work Item → Code → Verification → Evidence → Release`

Development is iterative; documentation is progressively elaborated. We do not wait for every future document to be complete before coding, but the next implementation decision must have enough requirement/interface definition to avoid uncontrolled divergence.

## Kanban states
`Backlog → Ready → In Progress → Review → Verification → Field/HIL (when applicable) → Done`

WIP is limited so incomplete integration work does not accumulate.

## Definition of Done
A work item is Done only when applicable items are complete:
- requirement/issue is identifiable;
- architecture/interface impact reviewed;
- code follows the layered/ports-and-adapters boundaries;
- automated tests cover normal, negative, boundary and regression behavior;
- failure/recovery behavior is considered;
- documentation/traceability updated;
- build is warning-clean;
- relevant evidence is stored or referenced;
- rollback/recovery path exists for high-impact changes.

## Milestone gates
- **G0** Development readiness
- **M0** Sensing feasibility
- **M1** Single-node prototype
- **M2** 3-node distributed cluster
- **M3** One-side ~20 m pilot
- **M4** Full perimeter candidate (~16 nodes)
- **M5** Operational acceptance

Software can progress in parallel with sensing experiments by using mocks/fakes/simulators.
