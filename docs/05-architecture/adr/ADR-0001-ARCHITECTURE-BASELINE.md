# ADR-0001 — Local-first composable architecture
Status: Accepted

## Decision
Use layered responsibility boundaries with Ports/Adapters, event-driven behavior, explicit state machines and composable replaceable blocks. Local sensing/event handling shall not depend on Internet availability.

## Consequences
Hardware/network/storage implementations remain replaceable and testable with fakes. Interfaces become controlled contracts. Additional abstraction is justified only at likely change boundaries; embedded resource cost must be measured on target.
