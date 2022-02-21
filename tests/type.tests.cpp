#include <gtest/gtest.h>
#include "meta/type.hpp"

TEST(TypeTest, TypeOfScalar) {
    int i = 0;
    static_assert(std::is_same_v<putils_typeof(i), int>);
    SUCCEED();
}

TEST(TypeTest, TypeOfRef) {
    int i = 0;
    const int & ref = i;
    static_assert(std::is_same_v<putils_typeof(ref), int>);
    SUCCEED();
}

TEST(TypeTest, Wrapped) {
    static_assert(std::is_same_v<putils::meta::type<int>::wrapped, int>);
    SUCCEED();
}