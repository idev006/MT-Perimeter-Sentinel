# Project Charter

| Document ID | MPS-PM-CHARTER-001 |
|---|---|
| Version | 1.0 |
| Status | BASELINED |

## Mission
Create a camera-free distributed electronic perimeter intrusion-detection system for an initial ~20 m × 20 m site. Approximately 16 nodes cooperate as one virtual fence rather than acting as isolated sensors.

## Objectives
- Detect approaching/crossing/leaving/loitering candidates with measurable confidence.
- Correlate evidence across nodes to estimate path/direction and suppress single-sensor noise.
- Continue local detection, incident formation, logging and CCOC visibility when Internet is unavailable.
- Survive and recover from common network, power, node, gateway, configuration, storage and update failures without silent loss of critical events.
- Support maintainable C++/ESP-IDF implementation using replaceable components and stable contracts.
- Support safe remote/local OTA, including gateway-relayed OTA for child nodes that do not directly join Wi-Fi.
- Provide auditable CCOC command/control and degraded-capability reporting.

## Non-goals for v1
- Camera/video identification.
- Guaranteed person identification.
- Claiming life-safety certification without independent certification/testing.

## Budget governance
Use progressive procurement: research → one node → three-node cluster → one-side pilot → full perimeter. Hardware purchase is gated by evidence from the previous stage.

## Success condition
Operational v1.0 requires M5 acceptance and physical HIL/field evidence. Host simulation alone cannot authorize deployment.
