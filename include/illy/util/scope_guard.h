#pragma once

#include <iostream>

namespace illy {

template <typename EF>
class scope_guard {
public:

    static_assert(std::is_object_v<EF>, "Scope guard requires a valid FunctionObject, failed object check.");
    static_assert(std::is_invocable_v<EF>, "Scope guard requires a valid FunctionObject, failed invocable check.");
    static_assert(std::is_destructible_v<EF>, "Scope guard requires a destructible FunctionObject");

    scope_guard() = default;

    explicit scope_guard(const EF exit_func) : exit_function_{std::move(exit_func)}
    {
        active_ = true;
    }

    ~scope_guard()
    {
        if (active_) {
            std::invoke(exit_function_);
        }
    }

    scope_guard(scope_guard&& other) noexcept : exit_function_{std::move(other.exit_function_)}
    {
        other.release();
        active_ = true;
    }
    scope_guard(const scope_guard&) = delete;
    scope_guard& operator=(const scope_guard&) = delete;
    scope_guard& operator=(scope_guard&&) = delete;

    void release()
    {
        active_ = false;
    }
private:
    bool active_ = false;
    EF exit_function_;
};

} //namespace illy
