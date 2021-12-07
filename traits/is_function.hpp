#pragma once

#include "details/function_traits.hpp"

namespace putils {
	template<typename T>
	using is_function = detail::function_traits<std::decay_t<T>>;
}