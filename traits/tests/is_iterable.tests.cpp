#include <gtest/gtest.h>
#include "meta/traits/is_iterable.hpp"

TEST(IsIterableTest, Array) {
    static_assert(putils::is_iterable<bool[2]>());
    SUCCEED();
}

TEST(IsIterableTest, Pointer) {
    static_assert(!putils::is_iterable<bool *>());
    SUCCEED();
}

TEST(IsIterableTest, Vector) {
    static_assert(putils::is_iterable<std::vector<bool>>());
    SUCCEED();
}

TEST(IsIterableTest, Map) {
    static_assert(putils::is_iterable<std::map<int, bool>>());
    SUCCEED();
}

TEST(IsIterableTest, False) {
    static_assert(!putils::is_iterable<int>());
    SUCCEED();
}
