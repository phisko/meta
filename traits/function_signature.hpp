#pragma once

#include "details/function_traits.hpp"

namespace putils {
	template<typename T>
	using function_signature = typename detail::function_traits<std::decay_t<T>>::signature;
}