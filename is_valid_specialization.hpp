#ifndef IS_VALID_SPECIALIZATION_INCLUDED_
#define IS_VALID_SPECIALIZATION_INCLUDED_

#include "sfinae.hpp"
#include <type_traits>

namespace tmpl {
	namespace detail {

		template<template<typename...> class C, typename... T>
		struct is_valid_specialization_impl {

			template<template<typename...> class D>
			static sfinae::yes test(D<T...>*);
			template<template<typename...> class D>
			static sfinae::no test(...);

			using type = 	typename std::conditional<
								(sizeof(test<C>(0)) == sizeof(sfinae::yes)),
								std::true_type,
								std::false_type
							>::type;
		};
	}

	template<template<typename...> class C, typename... T>
	struct is_valid_specialization : detail::is_valid_specialization_impl<C, T...>::type { };
}

#endif
