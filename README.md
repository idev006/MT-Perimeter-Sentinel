# MT-Perimeter-Sentinel

Distributed, camera-free electronic perimeter intrusion-detection reference project.

## Status
Pre-HIL reconstructed reference baseline. C++ is the primary firmware/domain language; C is reserved for ESP-IDF/low-level driver integration.

## Architecture
Layered + Ports/Adapters + Event-Driven + Composable Blocks.

## Build and verify
```bash
make verify-all
```

## Evidence classification
HOST_VERIFIED / SIMULATED / HIL_REQUIRED / FIELD_REQUIRED.

Operational deployment is **not authorized** until HIL and field acceptance gates pass.
