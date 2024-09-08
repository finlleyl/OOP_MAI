.PHONY: build run test

build: clean-build
	@mkdir -p build
	@git submodule init
	@git submodule update
	@cd build && cmake .. && make main && make test

run: @./build/main

test: @./build/test

clean-build: @rm -rf ./build/