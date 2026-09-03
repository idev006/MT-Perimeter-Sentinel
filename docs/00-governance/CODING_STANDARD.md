# C++ / Firmware Coding Standard

| Field | Value |
|---|---|
| Document ID | MPS-DEV-CODE-001 |
| Version | 1.0 |
| Status | BASELINED |

## Baseline
- C++ is the default firmware/domain language; C is used for low-level ESP-IDF/vendor APIs when appropriate.
- Host reference uses C++20; target code shall use the subset supported by the selected ESP-IDF/toolchain and record any deviations.
- GCC/Clang host builds use `-Wall -Wextra -Wpedantic -Werror`.
- Host verification includes AddressSanitizer and UndefinedBehaviorSanitizer.

## Mandatory engineering rules
1. Domain code depends on interfaces/ports, not concrete sensors/radios/storage/services.
2. Long-running queues, replay caches and embedded collections must be bounded or have an explicit retention/compaction policy.
3. Error/failure states must be explicit; important failures must not be silently swallowed.
4. Safety/security-impacting changes use stage/verify/commit/rollback when applicable.
5. No plaintext secrets/private keys in source, logs, audit records or repository history.
6. Audit logs record command identity/action/result, not raw secret-bearing payloads.
7. Magic topology values and hidden cross-module assumptions are prohibited where a contract already owns that information.
8. New defects require regression tests before closure.
9. Header-only components are acceptable for the reference baseline but target resource/timing impact must be measured on ESP32.
10. Comments document intent/invariants, not restate obvious syntax.

## Review checklist
Dependency direction; bounds/resource lifetime; failure/recovery; concurrency assumptions; data integrity; authorization; test coverage; requirement/ADR impact; target constraints.
