// gtest
#include <gtest/gtest.h>

// meta
#include "traits/is_unstreamable.hpp"

TEST(is_unstreamable, string) {
    static_assert(putils::is_unstreamable<std::istream, std::string>());
    SUCCEED();
}

TEST(is_unstreamable, vector) {
    static_assert(!putils::is_unstreamable<std::istream, std::vector<bool>>());
    SUCCEED();
}

TEST(is_unstreamable, scalar) {
    static_assert(putils::is_unstreamable<std::istream, int>());
    SUCCEED();
}

TEST(is_unstreamable, not_stream) {
    static_assert(!putils::is_unstreamable<int, std::string>());
    SUCCEED();
}
