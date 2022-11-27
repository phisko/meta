#pragma once

// meta
#include "details/member_function_traits.hpp"

namespace putils {
	template<typename T>
	using is_member_function_ptr = detail::member_function_traits<std::decay_t<T>>;
}