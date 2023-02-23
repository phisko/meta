#pragma once

// meta
#include "putils/meta/traits/details/member_function_traits.hpp"

namespace putils {
	template<typename T>
	concept member_function_ptr = detail::member_function_traits<std::decay_t<T>>::value;
}