#include <gtest/gtest.h>
#include "meta/traits/has_member.hpp"

struct Yes {
    int i = 42;
};

struct No {
};

putils_member_detector(i);

TEST(has_member, true) {
    static_assert(has_member_i<Yes>());
    SUCCEED();
}

TEST(has_member, false) {
    static_assert(!has_member_i<No>());
    SUCCEED();
}
