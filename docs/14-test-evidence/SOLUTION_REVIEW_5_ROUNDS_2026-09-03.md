# Solution Review — Reliability-First — 5 Rounds — 2026-09-03

| Field | Value |
|---|---|
| Document ID | MPS-AUD-SOL-005 |
| Status | BASELINED-PRE-HIL |
| Scope | Solution, physical concept, sensing, network/power, software decision logic, integrated deployment |

## Context locked for this review
- Initial site: approximately 20 m x 20 m.
- Camera-free distributed perimeter detection.
- Budget cap: approximately THB 5,000 for the initial deployment stage.
- First field phase may instrument three sides before full perimeter expansion.
- Node physical concept: bamboo pole + birdhouse-like outer weather shield + protected electronics enclosure.
- Reliability is the primary success criterion. Target field detection effectiveness: >=80% for defined intrusion scenarios.
- Sustained confirmed alarms caused only by normal sun/heat/wind/rain/pole movement/animals are unacceptable.

## Round 1 — Mission and reliability
**Finding:** Existing mission/local-first/resilience objectives were sound, but reliability thresholds were not normative.

**Decision:** Add explicit detection, false-alarm, outdoor-environment and mechanical-stability requirements. Reliability failure blocks expansion.

## Round 2 — Sensor and physical installation
**Finding:** The birdhouse/bamboo concept is feasible only if treated as an outdoor sensor station, not as an unsealed hobby enclosure. Direct sun, condensation, insects, rain and pole sway can create both failures and nuisance detections.

**Decision:** Birdhouse is an outer weather shield. Electronics use a protected inner enclosure; sensor windows and rigid mounting are deliberate. Temperature/humidity and tamper/movement evidence are part of field acceptance. Sensor hardware remains subject to M0 testing rather than being prematurely locked.

## Round 3 — Network, power and failure behavior
**Finding:** Local-first architecture is correct. Within the THB 5,000 pilot, reliability is more important than maximizing redundancy or node count. Power instability, heat and frequent reboot can invalidate sensing metrics.

**Decision:** Use staged topology and evidence-driven spacing. Keep local sensing/correlation independent of Internet. Measure power, reset/brownout and enclosure temperature across day/night conditions before expansion.

## Round 4 — Software and decision logic
**Finding:** Ports/adapters and current fusion reference model support replaceable sensors, but a simple average of sensor confidence is not sufficient as a production intrusion classifier.

**Decision:** `single sensor trigger != confirmed intrusion`. Production policy must incorporate configured temporal, cross-sensor, cross-node and/or directional corroboration plus noisy-sensor suppression. Raw sensor triggers remain diagnostic events and do not automatically become alarms.

## Round 5 — Integrated solution
**Verdict:** APPROVED TO CONTINUE as a **three-side reliability pilot**, not yet an operational security deployment.

Planning range is approximately 10-13 nodes for three sides, but final node count/spacing is determined by M0 coverage evidence and budget. Do not lower enclosure/sensor quality simply to reach a desired node count.

## Mandatory gate before adding the fourth side
1. >=80% detection effectiveness on the approved human intrusion scenario set.
2. No sustained environment-driven confirmed intrusion alarms in defined sun/wind/rain/pole-movement tests.
3. No unexplained critical-event loss.
4. Health/coverage degradation is truthful and observable.
5. Mounting/enclosure/power behavior is acceptable through representative day/night conditions.

## Engineering implications
- Requirements updated: REQ-FUS-003, REQ-DET-001, REQ-FP-001, REQ-ENV-001, REQ-MECH-001.
- Hazard analysis expanded for sun/thermal, wind/pole sway, rain/condensation, animals/insects, solar heating and budget dilution.
- HIL/field plan changed to three-side reliability pilot before full perimeter.
- Test specification now defines detection effectiveness, false confirmed incidents and environmental test families.

## Open implementation work
Current host fusion is a reference model. Before M0/M1 field acceptance, implement a configurable incident-decision policy with corroboration/time-window/noisy-sensor handling and evidence logging suitable for measuring REQ-DET-001/REQ-FP-001.

## Final rule
A system that merely generates many detections is not successful. The project succeeds only when operators can trust the alarms. Reliability evidence takes precedence over node count, feature count and cosmetic completion.
