#pragma once

#include <type_traits>
#include <functional>

namespace putils::detail {
#define SPECIALIZATION(TYPE) \
	template<typename R, typename ... Args> \
	struct function_traits< \
		TYPE \
	> : std::true_type { \
		using signature = R(*)(Args...);\
		using return_type = R; \
		using arguments = std::tuple<Args...>; \
	};

	template<typename T>
	struct function_traits : std::false_type {};

	SPECIALIZATION(R(*)(Args...))
	SPECIALIZATION(R(*)(Args...) noexcept)
	SPECIALIZATION(std::function<R(Args...)>)
#undef SPECIALIZATION
}