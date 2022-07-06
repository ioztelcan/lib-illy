/* Illy's Utilities */
#pragma once

#include <iostream>
#include <iterator>
#include <type_traits>
#include <vector>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <set>

namespace illy {

/* Container type traits */
template <typename T>
struct is_iter_container : std::false_type {};
template <typename... Args>
struct is_iter_container<std::vector<Args...>> : std::true_type {};
template <typename... Args>
struct is_iter_container<std::deque<Args...>> : std::true_type {};
template <typename... Args>
struct is_iter_container<std::list<Args...>> : std::true_type {};
template <typename... Args>
struct is_iter_container<std::forward_list<Args...>> : std::true_type {};
template <typename... Args>
struct is_iter_container<std::multiset<Args...>> : std::true_type {};
template <typename... Args>
struct is_iter_container<std::set<Args...>> : std::true_type {};

template <typename T>
constexpr bool is_iter_container_v = is_iter_container<T>::value;

template <typename T>
struct is_array : std::false_type {};
template <typename T, std::size_t U>
struct is_array<std::array<T,U>> : std::true_type {};

template <typename T>
constexpr bool is_array_v = is_array<T>::value;

/* Internal print() variants */

/* External print() overloads */
template <typename Iter>
void print(Iter beg, Iter end)
{
    std::cout << "[ ";
    while(beg != end) {
        std::cout << *beg << ' ';
        std::advance(beg, 1);
    }
    std::cout << "]\n";
}

template <typename T>
void print(T &&item)
{
    if constexpr (is_iter_container_v<std::remove_reference_t<T>>) {
        print(item.begin(), item.end());
    }
    else {
        std::cout << item << '\n';
    }
}

} //namespace illy
