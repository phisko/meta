// gtest
#include <gtest/gtest.h>

// meta
#include "putils/meta/traits/indexed_type.hpp"

template<typename T, typename Key, typename Expected>
using result = std::is_same<Expected, std::decay_t<putils::indexed_type<T, Key>>>;

TEST(indexed_type, array) {
	static_assert(result<float[2], int, float>());
	SUCCEED();
}

TEST(indexed_type, pointer) {
	static_assert(result<float *, int, float>());
	SUCCEED();
}

TEST(indexed_type, vector) {
	static_assert(result<std::vector<float>, int, float>());
	SUCCEED();
}

TEST(indexed_type, map) {
	static_assert(result<std::map<int, float>, int, float>());
	SUCCEED();
}

TEST(indexed_type, string_map) {
	static_assert(result<std::map<std::string, float>, std::string, float>());
	static_assert(result<std::map<std::string, float>, const char *, float>());
	SUCCEED();
}