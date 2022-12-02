#pragma once

namespace putils {
	template<typename T>
	concept indexable = requires(T obj) {
		obj[0];
	};
}