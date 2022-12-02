#pragma once

namespace putils {
	template<typename T, typename S>
	concept streamable = requires(const T & obj, S & stream) {
		stream << obj;
	};
}