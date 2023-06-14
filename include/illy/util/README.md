# illy::util

Collection of various utility functionality

## overload
Implementation of the overload pattern for lambda overloading.

Provides a struct called `overload_t` that can contain a set of lambdas that fit function overloading rules. It works by making the overload struct have an arbitrary amount of base classes. It publicly inherits each base class and brings the function call operator of each into its own scope. The function call operator overloads of the base classes are provided by the lambdas used in constructing `overload_t`.

It can be visited with a variant that would call the appropriate overload for each variant.

**Example:**

```cpp
    illy::overload_t identifier_func {
            [](int) {return "integer";},
            [](std::string) {return "string";},
            [](float) {return "float";},
    };

    identifier_func(5); // Output: integer
    identifier_func("asd"); // Output: string
```
