# HIL and Field Acceptance Plan

Sequence: single node -> 3-node cluster -> one-side ~20 m pilot -> 16-node perimeter -> soak/operational acceptance.

HIL must cover boot/reset/watchdog, event persistence, AP/Internet failure, credential migration, OTA rollback/brownout, storage, security, power, CCOC commands and audit.

Field must measure sensing accuracy/false alarms, RF range/interference, actual coverage gaps, power runtime, environmental effects, and 24h/72h/7d soak behavior.
