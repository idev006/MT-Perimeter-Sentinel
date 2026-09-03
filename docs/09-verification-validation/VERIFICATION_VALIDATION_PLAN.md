# Verification & Validation Plan

| Document ID | MPS-VVP-001 |
|---|---|
| Version | 1.1 |
| Status | BASELINED |

## Evidence ladder
`UNIT → CONTRACT → INTEGRATION → SIMULATED → HOST_VERIFIED → VIRTUAL_TARGET → HIL → FIELD → OPERATIONAL_ACCEPTANCE`

## Host release gate
`make verify-all` shall pass:
- strict compiler warnings (`-Wall -Wextra -Wpedantic -Werror`);
- unit/integration executable tests;
- reference store-and-forward simulation;
- ASan/UBSan build and execution.

## Mandatory scenario families
Normal path, invalid input, boundary capacity, duplicate/replay, packet/delivery failure, Internet outage, gateway outage/flapping, node/adjacent-node loss, bad config, failed OTA, power degradation, coverage interlock, unauthorized command, tampering, recovery and regression.

## Physical evidence rules
Host/simulation does **not** close RF, sensor accuracy, false alarms, power/runtime, flash endurance, real OTA partitioning, brownout/watchdog, weather/enclosure or site coverage requirements.

## Defect policy
A confirmed defect is not closed until the fix has regression coverage and relevant documentation/traceability is updated.
