#ifndef IS_VALID_SPECIALIZATION_INCLUDED_
#define IS_VALID_SPECIALIZATION_INCLUDED_

#include <type_traits>

namespace tmpl
{

namespace detail
{

template<template<typename...> class C, typename... T>
struct is_valid_specialization_impl
{
  template<template<typename...> class D>
  static std::true_type test(D<T...>*);
  template<template<typename...> class D>
  static std::false_type test(...);

  using type = decltype(test<C>(0));
};

} // namespace detail

template<template<typename...> class C, typename... T>
using is_valid_specialization = typename detail::is_valid_specialization_impl<C, T...>::type;

} // namespace tmpl

#endif
