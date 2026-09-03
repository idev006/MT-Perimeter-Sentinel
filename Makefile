.PHONY: build test sim sanitizers verify-all clean

build:
	cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
	cmake --build build -j2

test: build
	ctest --test-dir build --output-on-failure

sim: build
	./build/mps_sim

sanitizers:
	cmake -S . -B build-sanitize -DCMAKE_BUILD_TYPE=Debug -DMPS_ENABLE_SANITIZERS=ON
	cmake --build build-sanitize -j2
	ctest --test-dir build-sanitize --output-on-failure
	./build-sanitize/mps_sim

verify-all: test sim sanitizers

clean:
	rm -rf build build-sanitize
