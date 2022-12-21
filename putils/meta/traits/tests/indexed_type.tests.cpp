// gtest
#include <gtest/gtest.h>

// meta
#include "putils/meta/traits/indexed_type.hpp"

template<typename T>
using result = std::is_same<float, std::decay_t<putils::indexed_type<T>>>;

TEST(indexed_type, array) {
	static_assert(result<float[2]>());
	SUCCEED();
}

TEST(indexed_type, pointer) {
	static_assert(result<float *>());
	SUCCEED();
}

TEST(indexed_type, vector) {
	static_assert(result<std::vector<float>>());
	SUCCEED();
}

TEST(indexed_type, map) {
	static_assert(result<std::map<int, float>>());
	SUCCEED();
}
