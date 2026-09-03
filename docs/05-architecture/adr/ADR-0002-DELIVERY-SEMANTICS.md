# ADR-0002 — Durable at-least-once delivery
Status: Accepted

## Decision
Use at-least-once delivery with stable event IDs, idempotent processing and explicit delivery states. A sender may remove a critical event from durable backlog only after `DURABLE_LOCAL` or stronger acknowledgement.

## Rationale
Byte receipt is insufficient: a gateway can receive a frame and lose power before persisting it. Duplicate delivery is safer than silent loss when receivers are idempotent.

## Consequences
Queue/storage adapters must support peek-then-pop semantics; delivery/replay evidence must include restart and outage cases. Sequence tracking must permit gap closure by retransmission and use bounded state.
