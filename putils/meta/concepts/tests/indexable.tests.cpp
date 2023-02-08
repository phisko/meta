// gtest
#include <gtest/gtest.h>

// meta
#include "putils/meta/concepts/indexable.hpp"

TEST(indexable, array) {
	static_assert(putils::indexable<bool[2]>);
	static_assert(!putils::indexable<bool[2], std::string>);
	SUCCEED();
}

TEST(indexable, pointer) {
	static_assert(putils::indexable<bool *>);
	static_assert(!putils::indexable<bool *, std::string>);
	SUCCEED();
}

TEST(indexable, vector) {
	static_assert(putils::indexable<std::vector<bool>>);
	static_assert(!putils::indexable<std::vector<bool>, std::string>);
	SUCCEED();
}

TEST(indexable, map) {
	static_assert(putils::indexable<std::map<int, bool>>);
	static_assert(!putils::indexable<std::map<int, bool>, std::string>);
	SUCCEED();
}

TEST(indexable, string_map) {
	static_assert(!putils::indexable<std::map<std::string, bool>>);
	static_assert(putils::indexable<std::map<std::string, bool>, std::string>);
	static_assert(putils::indexable<std::map<std::string, bool>, const char *>);
	SUCCEED();
}

TEST(indexable, false) {
	static_assert(!putils::indexable<int>);
	static_assert(!putils::indexable<int, std::string>);
	SUCCEED();
}