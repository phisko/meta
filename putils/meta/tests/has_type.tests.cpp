// gtest
#include <gtest/gtest.h>

// meta
#include "putils/meta/has_type.hpp"

TEST(has_type, true) {
    static_assert(putils::has_type<bool, bool, int>());
    SUCCEED();
}

TEST(has_type, false) {
    static_assert(!putils::has_type<bool, double, int>());
    SUCCEED();
}
