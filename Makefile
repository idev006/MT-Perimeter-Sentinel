.PHONY: build test sim verify-all clean
build:
	cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
	cmake --build build -j2
test: build
	ctest --test-dir build --output-on-failure
sim: build
	./build/mps_sim
verify-all: test sim
clean:
	rm -rf build
