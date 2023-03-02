// gtest
#include <gtest/gtest.h>

// meta
#include "putils/meta/concepts/enumeration.hpp"

TEST(enumeration, true) {
	enum e {};
	static_assert(putils::enumeration<e>);
	SUCCEED();
}

TEST(enumeration, false) {
	static_assert(!putils::enumeration<int>);
	SUCCEED();
}