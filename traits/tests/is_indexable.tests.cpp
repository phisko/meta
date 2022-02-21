#include <gtest/gtest.h>
#include "meta/traits/is_indexable.hpp"

TEST(IsIndexableTest, Array) {
    static_assert(putils::is_indexable<bool[2]>());
    SUCCEED();
}

TEST(IsIndexableTest, Pointer) {
    static_assert(putils::is_indexable<bool *>());
    SUCCEED();
}

TEST(IsIndexableTest, Vector) {
    static_assert(putils::is_indexable<std::vector<bool>>());
    SUCCEED();
}

TEST(IsIndexableTest, Map) {
    static_assert(putils::is_indexable<std::map<int, bool>>());
    SUCCEED();
}

TEST(IsIndexableTest, False) {
    static_assert(!putils::is_indexable<int>());
    SUCCEED();
}