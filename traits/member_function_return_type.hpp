#pragma once

// meta
#include "details/member_function_traits.hpp"

namespace putils {
	template<typename T>
	using member_function_return_type = typename detail::member_function_traits<std::decay_t<T>>::return_type;
}