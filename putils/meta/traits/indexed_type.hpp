#pragma once

// stl
#include <type_traits>

namespace putils {
	template<typename T, typename Index = int>
	using indexed_type = decltype(std::declval<T>()[std::declval<Index>()]);
}