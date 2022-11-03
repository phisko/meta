// gtest
#include <gtest/gtest.h>

// meta
#include "traits/is_indexable.hpp"

TEST(is_indexable, array) {
    static_assert(putils::is_indexable<bool[2]>());
    SUCCEED();
}

TEST(is_indexable, pointer) {
    static_assert(putils::is_indexable<bool *>());
    SUCCEED();
}

TEST(is_indexable, vector) {
    static_assert(putils::is_indexable<std::vector<bool>>());
    SUCCEED();
}

TEST(is_indexable, map) {
    static_assert(putils::is_indexable<std::map<int, bool>>());
    SUCCEED();
}

TEST(is_indexable, false) {
    static_assert(!putils::is_indexable<int>());
    SUCCEED();
}