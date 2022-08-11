# Utillyty
A header only C++ library with helper functions and other stuff. Mainly created for personal use, not recommended for production.

Currenty only has type erased print functions and works with C++ 17.

## Usage

- Simply add the header "utillyty.h" to your project. Usable functions are in namespace `illy`.

## Dependencies

- Requires C++ 17

## Functions

### print

- Utillyty has a type erased `print` function that works with:
    - Primitive types.
    - String literals.
    - Most of the STL containers.
    - Custom classes with overloaded `operator <<` functions.
    - Ranges provided with two iterators.

It does not support taking more than one argument (except for iterator ranges), or selecting a custom output stream yet. Everything is send to `std::cout`. After every print a newline is added.

**Example:**
```cpp
std::vector ivec {1,2,3,4,5,6};
illy::print(ivec);
// Output: [ 1, 2, 3, 4, 5, 6 ]

illy::print("Hello!");
// Output: Hello!
