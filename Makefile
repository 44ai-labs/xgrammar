
.PHONY: build

build:
	cd build && ninja
	cd python && python3 -m pip install .
