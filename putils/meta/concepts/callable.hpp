#pragma once

// meta
#include "putils/meta/traits/details/function_traits.hpp"

namespace putils {
	template<typename T>
	concept callable = detail::function_traits<std::decay_t<T>>::value;
}