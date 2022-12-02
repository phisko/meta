#pragma once

namespace putils {
	template<typename T, typename S>
	concept unstreamable = requires(T & obj, S & stream) {
		stream >> obj;
	};
}