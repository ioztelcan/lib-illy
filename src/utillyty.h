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
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <tuple>

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
template <typename... Args>
struct is_iter_container<std::unordered_set<Args...>> : std::true_type {};
template <typename... Args>
struct is_iter_container<std::unordered_multiset<Args...>> : std::true_type {};
template <typename T, std::size_t U>
struct is_iter_container<std::array<T,U>> : std::true_type {};
template <typename T>
constexpr bool is_iter_container_v = is_iter_container<T>::value;

template <typename... Args>
struct is_container_adaptor : std::false_type {};
template <typename... Args>
struct is_container_adaptor<std::stack<Args...>> : std::true_type {};
template <typename... Args>
struct is_container_adaptor<std::queue<Args...>> : std::true_type {};
template <typename... Args>
struct is_container_adaptor<std::priority_queue<Args...>> : std::true_type {};
template <typename T>
constexpr bool is_container_adaptor_v = is_container_adaptor<T>::value;

template <typename T>
struct is_queue : std::false_type {};
template <typename... Args>
struct is_queue<std::queue<Args...>> : std::true_type {};
template <typename T>
constexpr bool is_queue_v = is_queue<T>::value;

template <typename N>
struct is_str_literal: std::false_type {};
template <std::size_t N>
struct is_str_literal<const char [N]> : std::true_type {};
template <typename T>
constexpr bool is_str_literal_v = is_str_literal<T>::value;

template <typename T>
struct is_unordered_map : std::false_type {};
template <typename... Args>
struct is_unordered_map<std::unordered_map<Args...>> : std::true_type {};
template <typename... Args>
struct is_unordered_map<std::unordered_multimap<Args...>> : std::true_type {};
template <typename T>
constexpr bool is_unordered_map_v = is_unordered_map<T>::value;

template <typename T>
struct is_pair : std::false_type {};
template <typename T1, typename T2>
struct is_pair<std::pair<T1, T2>> : std::true_type {};
template <typename T>
constexpr bool is_pair_v = is_pair<T>::value;

// template <typename T>
// struct is_tuple : std::false_type {};
// template <typename ...Args>
// struct is_tuple<std::tuple<Args...>> : std::true_type {};
// template <typename T>
// constexpr bool is_tuple_v = is_tuple<T>::value;

/* Internal print() variants */
namespace print_impl {

template <typename T>
void print_container_adaptor(T input)
{
    std::cout << "[ ";
    while (!input.empty()) {
        if constexpr(is_queue_v<T>) {
            std::cout << input.front() << ' ';
        }
        else {
            std::cout << input.top() << ' ';
        }
        input.pop();
    }
    std::cout << "]\n";
}

template <typename T>
void print_c_array(const T &input)
{
    if constexpr (is_str_literal_v<T>) {
        std::cout << input << '\n';
    }
    else {
        std::cout << "[ ";
        for (const auto &val : input) {
            std::cout << val << ' ';
        }
        std::cout << "]\n";
    }
}

template <typename T>
void print_unordered_map(const T input)
{
    std::cout << "[ ";
    for (const auto &[key, val] : input) {
        std::cout << '{' << key << ':' << val << '}' << ' ';
    }
    std::cout << "]\n";
}

// template <std::size_t ...Idx>
// struct tuple_index;

// template <typename T, std::size_t... Is>
// void print_tuple(T &input, std::index_sequence<Is...>)
// {
//     std::cout << "{ ";
//     std::cout << std::get<Is>(input) << ' ';
//     std::cout << "}\n";
// }

} //namespace print_impl

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
void print(T &&input)
{
    if constexpr (is_iter_container_v<std::remove_reference_t<T>>) {
        print(input.begin(), input.end());
    }
    else if constexpr (is_container_adaptor_v<std::remove_reference_t<T>>) {
        print_impl::print_container_adaptor(input);
    }
    else if constexpr (std::is_array_v<std::remove_reference_t<T>>) {
        print_impl::print_c_array(input);
    }
    else if constexpr (is_unordered_map_v<std::remove_reference_t<T>>) {
        print_impl::print_unordered_map(input);
    }
    else if constexpr (is_pair_v<std::remove_reference_t<T>>) {
        const auto &[key, val] = input;
        std::cout << '{' << key << ':' << val << '}' << '\n';
    }
    // else if constexpr (is_tuple_v<std::remove_reference_t<T>>) {
    //     constexpr auto tp_size = std::tuple_size_v<std::remove_reference_t<T>>;
    //     print_impl::print_tuple(input, std::make_index_sequence<tp_size>{});
    // }
    else {
        std::cout << input << '\n';
    }
}

} //namespace illy
