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

	template<typename R, size_t Size, typename ... Args>
	struct function_traits<
		putils::function<R(Args...), Size>
	> : std::true_type {
		using signature = R(*)(Args...);
		using return_type = R;
		using arguments = std::tuple<Args...>;
	};
#undef SPECIALIZATION
}