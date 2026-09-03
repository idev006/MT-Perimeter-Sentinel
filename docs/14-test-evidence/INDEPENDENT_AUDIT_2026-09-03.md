# Independent Conformance Audit — 2026-09-03

## Scope
GitHub SSOT documentation, C++ host/reference source, ESP-IDF skeleton, tests, CI, requirements-to-feature traceability and alignment with the perimeter-security mission.

## Findings corrected in this audit
1. **Topology hard-code defect:** correlation wrap-around assumed 16 nodes despite generic ring constructor. Corrected to topology-driven step direction and added non-16 regression.
2. **CCOC semantic contradiction:** Internet outage forced whole system DEGRADED despite local-first mission. Corrected by separating perimeter health from external connectivity.
3. **Durable-delivery ambiguity:** boolean `send()` allowed local queue removal without distinguishing byte receipt vs durable receiver storage. Added delivery-state contract; queued event is removed only on `DURABLE_LOCAL` or stronger.
4. **State model gap:** INITIALIZING state existed but was unreachable. Added BOOT_COMPLETE/INIT transitions and failure path.
5. **Sensor-fusion order/input issues:** now uses best valid observation per sensor type, ignores stale/future/invalid confidence.
6. **Wireless/config lifecycle too weak:** added explicit candidate/verification/commit, preservation of previous profile/config and rollback behavior.
7. **OTA lifecycle too weak:** replaced direct version switch with stage/boot/self-test/commit/rollback reference states.
8. **Authorization too coarse:** added action-based RBAC and audited idempotent command service.
9. **Security requirement had no cryptographic host evidence:** added HMAC-SHA-256 host authenticator and replay guard.
10. **Host quality gate incomplete:** added ASan/UBSan execution to `make verify-all` and CI.
11. **Engineering documents were summary-only:** expanded CONOPS, requirements, architecture, ICD, security, failure modes, V&V, HIL/field plan, CM and risk register.

## Residual limitations (not software audit failures)
- ESP-IDF target adapter/build/run has not yet been physically verified.
- Persistent flash/NVS event/config/command/audit adapters require HIL verification.
- Gateway-relayed OTA is architected/contracted but requires real local-radio transport implementation and HIL.
- Full CCOC operational UI/API remains a target capability beyond the current host health/reference model.
- RF, sensor accuracy/false alarm, power/runtime, enclosure/environment and field coverage require physical evidence.

## Conclusion
After the remediation commit and green CI, the repository is suitable as a **pre-HIL engineering baseline**, not as an operationally authorized security deployment.
