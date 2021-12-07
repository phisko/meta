#pragma once

#include "details/member_function_traits.hpp"

namespace putils {
	template<typename T>
	using member_function_decay = typename detail::member_function_traits<std::decay_t<T>>::decay;
}