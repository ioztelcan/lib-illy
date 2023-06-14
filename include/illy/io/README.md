# illy::io

Collection of input/output related functionality

TODO: complete the README

## print

This header has a type erased `print` function that works with:
- Primitive types.
- String literals.
- Most of the STL containers.
- Custom classes with overloaded `operator <<` functions.
- Ranges provided with two iterators.

> **Warning**
> - It does not support taking more than one argument (except for iterator ranges), or selecting a custom output stream yet. 
> - Everything is sent to `std::cout`. 
> - After every print a newline is added.

**Example:**
```cpp
std::vector ivec {1,2,3,4,5,6};
illy::print(ivec);
// Output: [ 1, 2, 3, 4, 5, 6 ]
illy::print("Hello!");
// Output: Hello!