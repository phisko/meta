#pragma once

#include "details/function_traits.hpp"

namespace putils {
	template<typename T>
	using function_arguments = typename detail::function_traits<std::decay_t<T>>::arguments;
}