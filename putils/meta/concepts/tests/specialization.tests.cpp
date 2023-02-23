// gtest
#include <gtest/gtest.h>

// meta
#include "putils/meta/traits/is_specialization.hpp"

TEST(is_specialization, vector) {
	static_assert(putils::is_specialization<std::vector<bool>, std::vector>());
	SUCCEED();
}

TEST(is_specialization, map) {
	static_assert(putils::is_specialization<std::map<int, bool>, std::map>());
	SUCCEED();
}

TEST(is_specialization, false) {
	static_assert(!putils::is_specialization<std::map<int, bool>, std::vector>());
	SUCCEED();
}