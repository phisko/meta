#pragma once

#include <type_traits>

namespace putils::detail {
#define SPECIALIZATION(TYPE) \
	template<typename T, typename R, typename ... Args> \
	struct member_function_traits< \
		TYPE \
	> : std::true_type { \
		using decay = R(T::*)(Args...); /* Remove const noexcept */ \
		using signature = R(Args...); \
		using return_type = R; \
		using arguments = std::tuple<Args...>; \
	};

	template<typename T>
	struct member_function_traits : std::false_type {};

	SPECIALIZATION(R(T::*)(Args...))
	SPECIALIZATION(R(T::*)(Args...) const)
	SPECIALIZATION(R(T::*)(Args...) noexcept)
	SPECIALIZATION(R(T::*)(Args...) const noexcept)
#undef SPECIALIZATION
}