#include <gtest/gtest.h>
#include "meta/nameof.hpp"

struct Obj {
    int _i = 42;
};

TEST(NameOfTest, NameOf) {
    EXPECT_EQ(std::string_view("Obj"), putils_nameof(Obj));
}

TEST(NameOfTest, NameOfPrivate) {
    EXPECT_EQ(std::string_view("i"), putils_nameof_private(_i));
}