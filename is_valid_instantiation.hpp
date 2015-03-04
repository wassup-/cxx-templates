#ifndef IS_VALID_INSTANTIATION_INCLUDED_
#define IS_VALID_INSTANTIATION_INCLUDED_

#include <type_traits>

namespace tmpl
{

namespace detail
{

template<template<typename...> class C, typename... T>
struct is_valid_instantiation_impl
{
  // Default constructor
  template<template<typename...> class D>
  static std::true_type test(decltype(D<T...>{ })*, int);
  // Copy constructor
  template<template<typename...> class D>
  static std::true_type test(decltype(D<T...>{ std::declval<const D<T...>&>() })*, long);
  // Move constructor
  template<template<typename...> class D>
  static std::true_type test(decltype(D<T...>{ std::declval<D<T...>&&>() })*, int*);

  template<template<typename...> class D>
  static std::false_type test(...);

  using type = decltype(test<C>(nullptr, 1));
};

} // namespace detail

template<template<typename...> class C, typename... T>
using is_valid_instantiation = typename detail::is_valid_instantiation_impl<C, T...>::type;

} // namespace tmpl

#endif
