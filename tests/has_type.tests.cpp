#include <gtest/gtest.h>
#include "meta/has_type.hpp"

TEST(HasTypeTest, True) {
    static_assert(putils::has_type<bool, bool, int>());
    SUCCEED();
}

TEST(HasTypeTest, False) {
    static_assert(!putils::has_type<bool, double, int>());
    SUCCEED();
}
