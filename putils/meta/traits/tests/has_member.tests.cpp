// gtest
#include <gtest/gtest.h>

// meta
#include "putils/meta/traits/has_member.hpp"

struct yes {
    int i = 42;
};

struct no {
};

putils_member_detector(i);

TEST(has_member, true) {
    static_assert(has_member_i<yes>());
    SUCCEED();
}

TEST(has_member, false) {
    static_assert(!has_member_i<no>());
    SUCCEED();
}
