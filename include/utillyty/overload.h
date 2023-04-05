#pragma once

namespace illy {

/**
 * Overload pattern
 *
 * Allows for the creation of an object that can provide one callable overlaoded with different lambdas
 *
 * The Types to be passed are lambdas. To make them work with a variant + visit the return types must be the same.
 */
template<typename ... Ts>
struct overload_t : Ts ... { //publicly inherit passed types
  using Ts::operator() ...; // include the base func call operator to this scope
};
template<typename... Ts> overload_t(Ts...) -> overload_t<Ts...>; // This is required for C++17 as a deduction guide to tell the compiler how to create out-of-constructor arguments template parameters

} //namespace illy