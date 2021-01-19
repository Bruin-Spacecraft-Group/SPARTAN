default: standard-build

BUILD_DIRECTORY := "_build"

# Added to avoid verbose printing of "entering/leaving directory" outputted messages
standard-build:
	make build --no-print-directory

build:
	cmake -B $(BUILD_DIRECTORY)
	cmake --build $(BUILD_DIRECTORY)

run: standard-build
	./"$(BUILD_DIRECTORY)"/main/spartan

lint: standard-build
	# TODO: Add linting scripts

test: standard-build
	# TODO: Add testing infrastructure (could also include Valgrind/gdb testing as well)

clean:
	rm -rf $(BUILD_DIRECTORY)

.PHONY: default standard-build build run lint test clean