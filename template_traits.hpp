#ifndef TEMPLATE_TRAITS_INCLUDED_
#define TEMPLATE_TRAITS_INCLUDED_

#include "is_valid_instantiation.hpp"
#include "is_valid_specialization.hpp"

#include <type_traits>

#if !defined(TEMPLATE_ARGS_MAX_RECURSION)
	#define TEMPLATE_ARGS_MAX_RECURSION 30
#endif

namespace tmpl
{

namespace detail
{

enum class specialization_state {
	invalid,
	valid,
	invalid_again
};

template<bool, template<typename...> class C, typename... T>
struct num_arguments_min
: std::integral_constant<int, sizeof...(T)>
{ };

template<template<typename...> class C, typename... T>
struct num_arguments_min<false, C, T...>
: num_arguments_min<is_valid_specialization<C, T..., char>::value, C, T..., char>
{ };

template<specialization_state, template<typename...> class C, typename... T>
struct num_arguments_max;

template<template<typename...> class C, typename... T>
struct num_arguments_max<specialization_state::invalid, C, T...>
: num_arguments_max<
	is_valid_specialization<C, T..., char>::value
		? specialization_state::valid
		: specialization_state::invalid,
	C,
	T...,	char
>
{ };

template<template<typename...> class C, typename... T>
struct num_arguments_max<specialization_state::valid, C, T...>
: std::conditional<
	((sizeof...(T) == 0) || (sizeof...(T) == TEMPLATE_ARGS_MAX_RECURSION)),
	std::integral_constant<int, -1>,
	num_arguments_max<
		is_valid_specialization<C, T..., char>::value
			? specialization_state::valid
			: specialization_state::invalid_again,
		C,
		T...,	char
	>
>::type
{ };

template<template<typename...> class C, typename... T>
struct num_arguments_max<specialization_state::invalid_again, C, T...>
: std::integral_constant<int, (sizeof...(T) - 1)>
{ };

} // namespace detail

template<template<typename...> class C>
struct template_traits
{
	constexpr static int min_args = detail::num_arguments_min<is_valid_specialization<C>::value, C>::value;
	constexpr static int max_args = detail::num_arguments_max<is_valid_specialization<C>::value
																																		   ? detail::specialization_state::valid
																																		   : detail::specialization_state::invalid,
																																		 C>::value;

	constexpr static bool is_variadic = (max_args < min_args);

	template<typename... T>
	using specializable_with = is_valid_specialization<C, T...>;

	template<typename... T>
	using instantiable_with = is_valid_instantiation<C, T...>;
};

} // namespace tmpl

#endif
