# CPP Project Repo Template

A simple template repository to be a basis for cpp projects.

## Dependencies
- Meson build system (uses ninja as backend)
- (optional) Google Test
- (optional) Catch2

## Build Instructions

The Makefile provides a layer for simple usage. Following default rules are present:

**configure**
Configures the build environment with meson using the BUILD_DIR as the directory for build artifacts.

**clean**
Cleans the build artifacts. Does not remove the BUILD_DIR.

**test**
Runs meson test in the BUILD_DIR. Rule dependencies: `all`

**format**
Runs clang-format with the supplied `.clang-format` config file on all source files that are not in the subprojects directory.

**all**
Default rule to run make. Builds all the code. Rule dependencies: `configure`,`format`.

## Usage

Any usage documentation can come here.
