#include <gtest/gtest.h>
#include "meta/traits/has_member.hpp"

struct Yes {
    int i = 42;
};

struct No {
};

putils_member_detector(i);

TEST(HasMember, True) {
    static_assert(has_member_i<Yes>());
    SUCCEED();
}

TEST(HasMember, False) {
    static_assert(!has_member_i<No>());
    SUCCEED();
}
