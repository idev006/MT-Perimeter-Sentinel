# System Architecture

## Principles
- Layered by responsibility.
- Ports & Adapters for replaceable hardware/services.
- Event-driven asynchronous communication with explicit state machines.
- Composable LEGO-like blocks: standardized interfaces, lifecycle, health, configuration, and tests.
- Local-first, fail-soft, store-and-forward.

## Node layers
Application/Use Cases -> Domain -> Ports -> Adapters/Infrastructure -> ESP-IDF/HAL.

## Major blocks
Sensor, Sensor Fusion, Event Bus, Node Core, State Machine, Transport, Event Store, Configuration, Health, Power Policy, OTA.

## System path
Sensors -> Node Core -> Local/Gateway Queue -> Correlation -> Incident -> CCOC -> Notification/External Integration.
