#pragma once

namespace putils {
	template<typename T, typename Index = int>
	concept indexable =
		requires(T obj, Index index) {
			obj[index];
		};
}