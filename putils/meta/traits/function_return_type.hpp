#pragma once

// meta
#include "details/function_traits.hpp"

namespace putils {
	template<typename T>
	using function_return_type = typename detail::function_traits<std::decay_t<T>>::return_type;
}