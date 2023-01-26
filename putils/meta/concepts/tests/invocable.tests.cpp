// gtest
#include <gtest/gtest.h>

// meta
#include "putils/meta/concepts/invocable.hpp"

TEST(indexable, function) {
	using type = int(float, double);
	static_assert(putils::invocable<type, int(float, double)>);
	SUCCEED();
}

TEST(indexable, function_pointer) {
	using type = int (*)(float, double);
	static_assert(putils::invocable<type, int(float, double)>);
	SUCCEED();
}

TEST(indexable, lambda) {
	const auto f = [](float, double) {
		return 0;
	};
	using type = decltype(f);
	static_assert(putils::invocable<type, int(float, double)>);
	SUCCEED();
}