BUILD_DIR="build"
BIN="main"

all: configure
	@meson compile -C ${BUILD_DIR}

clean:
	@ninja -C ${BUILD_DIR} clean

configure:
	@CC=clang-14 CXX=clang++-14 meson setup ${BUILD_DIR}

test: all
	@meson test -v -C ${BUILD_DIR}

format:
	@find . -not -path "./subprojects/*" -regex '.*\.\(cpp\|hpp\|cu\|c\|h\)' -exec clang-format-14 --verbose -style=file:.clang-format -i {} \;
	@echo "Formatting complete."

run:
	@echo "\n---------- Running ${BIN} ----------\n"
	@./${BUILD_DIR}/${BIN}

build-n-run: all run

.PHONY: configure test clean format
