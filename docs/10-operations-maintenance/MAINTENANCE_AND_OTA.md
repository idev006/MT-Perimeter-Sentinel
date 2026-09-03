# Maintenance and OTA

Initial provisioning should use controlled local flashing/provisioning. Routine updates use OTA. OTA is transport-independent: Wi-Fi is one transport; child nodes may receive relayed chunks through a gateway/local radio. Use inactive partition, integrity/signature verification, self-test, staged rollout, and rollback.
