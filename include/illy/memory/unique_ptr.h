#pragma once
#include <memory>
#include <type_traits>

namespace illy {

template <typename T, typename Deleter = std::default_delete<T>>
class unique_ptr {
    using pointer_t = T*;
    using element_t = T;
    using deleter_t = Deleter;

public:
    // Constructors
    explicit unique_ptr(std::nullptr_t in = nullptr): data_{nullptr} {}
    explicit unique_ptr(pointer_t in) : data_{in} {}

    unique_ptr(const unique_ptr& other)
    {
        if (other.data_) {
            data_ = new element_t{ *other.data_ };
        }
    }

    unique_ptr(unique_ptr&& other) noexcept : data_{other.release()}
    {}

    // Assignment operators
    unique_ptr& operator=(const unique_ptr& other) noexcept
    {
        if (&other == this) {
            return *this;
        }
        if (other.data_) {
            if (data_ != nullptr) {
                get_deleter()(data_);
                data_ = nullptr;
            }
            data_ = new element_t{ *other.data_ };
        }
        return *this;
    }

    unique_ptr& operator=(unique_ptr&& other) noexcept
    {
        data_ = other.release();
        return *this;
    }

    // Destructor
    ~unique_ptr() noexcept
    {
        if (data_ != nullptr) {
            get_deleter()(data_);
            data_ = nullptr;
        }
    }

    // Public Member functions
    deleter_t& get_deleter()
    {
        return deleter_;
    }

    pointer_t release() noexcept
    {
        auto* old_ptr = data_;
        data_ = nullptr;
        return old_ptr;
    }

    void reset(pointer_t in = nullptr) noexcept
    {
        this->~unique_ptr();
        data_ = in;
    }

    void swap(unique_ptr &other) noexcept
    {
        using std::swap;
        std::swap(*this, other);
    }

    // Instead of the traditional get, there is get_copy function to provide a deep copied version of the underlying resource
    unique_ptr<element_t, deleter_t> get_copy() noexcept
    {
        return unique_ptr<element_t, deleter_t> {*this};
    }

    explicit operator bool() const {
        return (data_ != nullptr);
    }

    element_t& operator*() const
    {
        return *data_;
    }

    pointer_t operator->() const noexcept
    {
        return data_;
    }

template< typename T1, typename D1, typename T2, typename D2 >
friend bool operator==(const unique_ptr<T1, D1>& lhs, const unique_ptr<T2, D2>& rhs);

template<typename T1, typename D1>
friend bool operator==(const unique_ptr<T1, D1>& lhs, std::nullptr_t);

template<typename T1, typename D1>
friend bool operator==(std::nullptr_t, const unique_ptr<T1, D1>& rhs);

template<typename T1, typename D1, typename T2, typename D2>
friend bool operator!=(const unique_ptr<T1, D1>& lhs, const unique_ptr<T2, D2>& rhs);

template<typename T1, typename D1>
friend bool operator!=(const unique_ptr<T1, D1>& lhs, std::nullptr_t);

template<typename T1, typename D1>
friend bool operator!=(std::nullptr_t, const unique_ptr<T1, D1>& rhs);

template<typename T1, typename D1, typename T2, typename D2>
friend bool operator<(const unique_ptr<T1, D1>& lhs, const unique_ptr<T2, D2>& rhs);

template<typename T1, typename D1>
friend bool operator<(const unique_ptr<T1, D1>& lhs, std::nullptr_t);

template<typename T1, typename D1>
friend bool operator<(std::nullptr_t, const unique_ptr<T1, D1>& rhs);

template<typename T1, typename D1, typename T2, typename D2>
friend bool operator<=(const unique_ptr<T1, D1>& lhs, const unique_ptr<T2, D2>& rhs);

template<typename T1, typename D1>
friend bool operator<=(const unique_ptr<T1, D1>& lhs, std::nullptr_t);

template<typename T1, typename D1>
friend bool operator<=(std::nullptr_t, const unique_ptr<T1, D1>& rhs);

template<typename T1, typename D1, typename T2, typename D2>
friend bool operator>(const unique_ptr<T1, D1>& lhs, const unique_ptr<T2, D2>& rhs);

template<typename T1, typename D1>
friend bool operator>(const unique_ptr<T1, D1>& lhs, std::nullptr_t);

template<typename T1, typename D1>
friend bool operator>(std::nullptr_t, const unique_ptr<T1, D1>& rhs);

template<typename T1, typename D1, typename T2, typename D2>
friend bool operator>=(const unique_ptr<T1, D1>& lhs, const unique_ptr<T2, D2>& rhs);

template<typename T1, typename D1>
friend bool operator>=(const unique_ptr<T1, D1>& lhs, std::nullptr_t);

template<typename T1, typename D1>
friend bool operator>=(std::nullptr_t, const unique_ptr<T1, D1>& rhs);

private:
    bool is_equal(const unique_ptr& other) const
    {
        return other.data_ == data_;
    }

    pointer_t data_ = nullptr;
    deleter_t deleter_ = Deleter{};
};

template<typename T>
void swap(unique_ptr<T>& lhs, unique_ptr<T>& rhs) noexcept
{
    lhs.swap(rhs);
}

template<typename T1, typename D1, typename T2, typename D2>
bool operator==(const unique_ptr<T1, D1>& lhs, const unique_ptr<T2, D2>& rhs)
{
    return lhs.is_equal(rhs);
}

template<typename T1, typename D1>
bool operator==(const unique_ptr<T1, D1>& lhs, std::nullptr_t)
{
    return !lhs;
}

template<typename T1, typename D1>
bool operator==(std::nullptr_t, const unique_ptr<T1, D1>& rhs)
{
    return !rhs;
}

template<typename T1, typename D1, typename T2, typename D2>
bool operator!=(const unique_ptr<T1, D1>& lhs, const unique_ptr<T2, D2>& rhs)
{
    return !lhs.is_equal(rhs);
}

template<typename T1, typename D1>
bool operator!=(const unique_ptr<T1, D1>& lhs, std::nullptr_t)
{
    return static_cast<bool>(lhs);
}

template<typename T1, typename D1>
bool operator!=(std::nullptr_t, const unique_ptr<T1, D1>& rhs)
{
    return static_cast<bool>(rhs);
}

template<typename T1, typename D1, typename T2, typename D2>
bool operator<(const unique_ptr<T1, D1>& lhs, const unique_ptr<T2, D2>& rhs)
{
    using CT = typename std::common_type<typename unique_ptr<T1, D1>::pointer_t, typename unique_ptr<T2, D2>::pointer_t>::type;
    return std::less<CT>()(lhs.data_, rhs.data_);
}

template<typename T1, typename D1>
bool operator<(const unique_ptr<T1, D1>& lhs, std::nullptr_t)
{
    return std::less<typename unique_ptr<T1, D1>::pointer_t>()(lhs.data_, nullptr);
}

template<typename T1, typename D1>
bool operator<(std::nullptr_t, const unique_ptr<T1, D1>& rhs)
{
    return std::less<typename unique_ptr<T1, D1>::pointer_t>()(nullptr, rhs.data_);
}

template<typename T1, typename D1, typename T2, typename D2>
bool operator<=(const unique_ptr<T1, D1>& lhs, const unique_ptr<T2, D2>& rhs)
{
    return !(rhs < lhs);
}

template<typename T1, typename D1>
bool operator<=(const unique_ptr<T1, D1>& lhs, std::nullptr_t)
{
    return !(nullptr < lhs);
}

template<typename T1, typename D1>
bool operator<=(std::nullptr_t, const unique_ptr<T1, D1>& rhs)
{
    return !(rhs < nullptr);
}

template<typename T1, typename D1, typename T2, typename D2>
bool operator>(const unique_ptr<T1, D1>& lhs, const unique_ptr<T2, D2>& rhs)
{
    return rhs < lhs;
}

template<typename T1, typename D1>
bool operator>(const unique_ptr<T1, D1>& lhs, std::nullptr_t)
{
    return nullptr < lhs;
}

template<typename T1, typename D1>
bool operator>(std::nullptr_t, const unique_ptr<T1, D1>& rhs)
{
    return rhs < nullptr;
}

template<typename T1, typename D1, typename T2, typename D2>
bool operator>=(const unique_ptr<T1, D1>& lhs, const unique_ptr<T2, D2>& rhs)
{
    return !(lhs < rhs);
}

template<typename T1, typename D1>
bool operator>=(const unique_ptr<T1, D1>& lhs, std::nullptr_t)
{
    return !(lhs < nullptr);
}

template<typename T1, typename D1>
bool operator>=(std::nullptr_t, const unique_ptr<T1, D1>& rhs)
{
    return !(nullptr < rhs);
}

template<typename T, typename ...Args>
unique_ptr<T> make_unique(Args&&... args)
{
    return unique_ptr<T>{ new T {std::forward<Args>(args)...} };
}

} //namespace illy