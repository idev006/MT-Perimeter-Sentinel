# Communication and Message Model

Message classes: Event, Command, Telemetry, Configuration.

Critical events require stable event_id, source, sequence, occurred_at, priority, schema version, and integrity/authentication metadata as appropriate.

Delivery model: at-least-once transport with idempotent processing. ACK states may include RECEIVED_LOCAL, DURABLE_LOCAL, DELIVERED_EXTERNAL, PROCESSED_EXTERNAL.
