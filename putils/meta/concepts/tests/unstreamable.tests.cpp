// gtest
#include <gtest/gtest.h>

// meta
#include "putils/meta/concepts/unstreamable.hpp"

TEST(unstreamable, string) {
	static_assert(putils::unstreamable<std::string, std::istream>);
	SUCCEED();
}

TEST(unstreamable, vector) {
	static_assert(!putils::unstreamable<std::vector<bool>, std::istream>);
	SUCCEED();
}

TEST(unstreamable, scalar) {
	static_assert(putils::unstreamable<int, std::istream>);
	SUCCEED();
}

TEST(unstreamable, not_stream) {
	static_assert(!putils::unstreamable<int, std::string>);
	SUCCEED();
}
