#ifndef IS_VALID_INSTANTIATION_INCLUDED_
#define IS_VALID_INSTANTIATION_INCLUDED_

#include "sfinae.hpp"
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
  static sfinae::yes test(decltype(D<T...>{ })*, int);
  // Copy constructor
  template<template<typename...> class D>
  static sfinae::yes test(decltype(D<T...>{ std::declval<const D<T...>&>() })*, long);
  // Move constructor
  template<template<typename...> class D>
  static sfinae::yes test(decltype(D<T...>{ std::declval<D<T...>&&>() })*, int*);

  template<template<typename...> class D>
  static sfinae::no test(...);

  using type =  typename std::conditional<(sizeof(test<C>(0, 1)) == sizeof(sfinae::yes)),
                                          std::true_type,
                                          std::false_type
                                          >::type;
};

} // namespace detail

template<template<typename...> class C, typename... T>
struct is_valid_instantiation : detail::is_valid_instantiation_impl<C, T...>::type { };

} // namespace tmpl

#endif
