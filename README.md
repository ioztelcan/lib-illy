# ILLY C++ Library

A collection of different libraries and functionalities to be used in C++ projects.

# Libraries

### [illy::io](include/illy/io/README.md)

Collection of input/output related functionality

- [illy::print](include/illy/io/README.md#print) - A type-erased print function that can work with most of the C++ containers and primitive types.

### [illy::util](include/illy/util/README.md)

Collection of various utility functionality

- [illy::overload](include/illy/io/README.md#overload) - Implementation of the overload pattern for lambda overloading.

### [illy::memory](include/illy/memory/README.md)

Collection of memory management related functionality

- [illy::unique_ptr](include/illy/io/README.md#unique_ptr) - A unique pointer implementation that deep copies underlying resource.


# Dependencies
- C++ 17 or higher
- cmake 3.24 or higher
- GoogleTest for unit tests

# Building Tests
- Create a build directory: `mkdir build && cd build`
- Run cmake with tests enabled flag: `cmake -DENABLE_ILLY_TESTING=1 ..`
- Run make `make`

# Running Tests

From within build directory, run:
- `./gtest/illy-test`

