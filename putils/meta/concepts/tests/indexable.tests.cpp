// gtest
#include <gtest/gtest.h>

// meta
#include "putils/meta/concepts/indexable.hpp"

TEST(indexable, array) {
    static_assert(putils::indexable<bool[2]>);
    SUCCEED();
}

TEST(indexable, pointer) {
    static_assert(putils::indexable<bool *>);
    SUCCEED();
}

TEST(indexable, vector) {
    static_assert(putils::indexable<std::vector<bool>>);
    SUCCEED();
}

TEST(indexable, map) {
    static_assert(putils::indexable<std::map<int, bool>>);
    SUCCEED();
}

TEST(indexable, false) {
    static_assert(!putils::indexable<int>);
    SUCCEED();
}