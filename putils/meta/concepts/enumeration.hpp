#pragma once

#include <type_traits>

namespace putils {
	template<typename T>
	concept enumeration = std::is_enum_v<T>;
}