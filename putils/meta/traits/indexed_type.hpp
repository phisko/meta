#pragma once

// stl
#include <type_traits>

namespace putils {
	template<typename T>
	using indexed_type = decltype(std::declval<T>()[(size_t)0]);
}