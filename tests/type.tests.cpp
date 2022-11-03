// gtest
#include <gtest/gtest.h>

// meta
#include "type.hpp"

TEST(type, typeof_scalar) {
    int i = 0;
    static_assert(std::is_same_v<putils_typeof(i), int>);
    SUCCEED();
}

TEST(type, typeof_ref) {
    int i = 0;
    const int & ref = i;
    static_assert(std::is_same_v<putils_typeof(ref), int>);
    SUCCEED();
}

TEST(type, wrapped) {
    static_assert(std::is_same_v<putils::meta::type<int>::wrapped, int>);
    SUCCEED();
}