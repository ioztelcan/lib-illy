# illy::memory

Collection of memory management related functionality

## unique_ptr

A unique pointer implementation that deep copies underlying resource.

It works the same way as STL's `std::unique_ptr` with the exception that it's copyable (deep copies the resource).

- It has a copy constructor and a copy assignment operator that deep copies the underlying resource.
- It doesn't have a `get()` member function. Instead, it has a `get_copy()` member function which returns a unique_ptr with a copy of the underlying resource.
- `illy::make_unique<T>()` factory function can be used in a similar fashion to STL equivalent.
- Supports providing a custom deleter type. Second template argument can be a custom deleter and by default it is `std::default_delete<T>`.

> **Warning**
> Similar to `std::unique_ptr`, comparison operators compare the pointer values of unique_ptrs, rather than comparing the resource.
 

**Example:**
```cpp

auto up1 = illy::make_unique<int>(10);

illy::unique_ptr up2{up1}; // now we have two integers alive.

auto up3 = up2.get_copy(); // now we have three alive.

illy::unique_ptr up4{std::move(up3)}; // we still have three integers alive, but four unique pointers. 

```