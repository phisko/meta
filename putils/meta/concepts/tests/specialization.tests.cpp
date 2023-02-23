// gtest
#include <gtest/gtest.h>

// meta
#include "putils/meta/concepts/specialization.hpp"

TEST(specialization, vector) {
	static_assert(putils::specialization<std::vector<bool>, std::vector>);
	SUCCEED();
}

TEST(specialization, map) {
	static_assert(putils::specialization<std::map<int, bool>, std::map>);
	SUCCEED();
}

TEST(specialization, false) {
	static_assert(!putils::specialization<std::map<int, bool>, std::vector>);
	SUCCEED();
}