# Maintenance and OTA Plan

| Document ID | MPS-OPS-OTA-001 |
|---|---|
| Version | 1.1 |
| Status | BASELINED |

## Provisioning
Initial commissioning uses controlled USB/UART or authorized local provisioning to establish bootloader/partitioning, device identity, trust anchors and network profiles. Routine maintenance should not require physical flashing.

## OTA design
OTA is transport-independent. Direct-Wi-Fi nodes may use HTTPS/local management; child nodes without Wi-Fi receive firmware through gateway-relayed local transport. The node itself verifies the candidate; a trusted gateway is not sufficient reason to trust firmware.

Lifecycle:
`STAGE → VERIFY signature/hash/compatibility → write inactive slot → boot candidate → self-test → COMMIT or ROLLBACK`

## Fleet rollout
Lab/reference → canary → small non-adjacent set → 25% → 50% → fleet. Coverage/power interlocks can pause rollout. Neighboring nodes should not be intentionally unavailable simultaneously where that creates a coverage gap.

## Relay protocol requirements
Manifest includes update ID, target HW/bootloader compatibility, version, size, digest and signature metadata. Chunks include update ID, offset/sequence, length and integrity check. Missing ranges are retransmitted without restarting the entire image.

## Maintenance cadence
Continuous health monitoring; regular log/false-alarm review; monthly physical inspection; quarterly enclosure/power/sensor review; controlled firmware/config release review.

## Recovery
USB/UART/local recovery remains available if management network/OTA is unusable. Failed OTA/config must preserve or restore a last-known-good operational state.
