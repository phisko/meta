// gtest
#include <gtest/gtest.h>

// meta
#include "putils/meta/traits/is_iterable.hpp"

TEST(is_iterable, array) {
    static_assert(putils::is_iterable<bool[2]>());
    SUCCEED();
}

TEST(is_iterable, pointer) {
    static_assert(!putils::is_iterable<bool *>());
    SUCCEED();
}

TEST(is_iterable, vector) {
    static_assert(putils::is_iterable<std::vector<bool>>());
    SUCCEED();
}

TEST(is_iterable, map) {
    static_assert(putils::is_iterable<std::map<int, bool>>());
    SUCCEED();
}

TEST(is_iterable, false) {
    static_assert(!putils::is_iterable<int>());
    SUCCEED();
}
