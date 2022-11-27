// gtest
#include <gtest/gtest.h>

// meta
#include "nameof.hpp"

struct Obj {
    int _i = 42;
};

TEST(nameof, nameof) {
    EXPECT_EQ(std::string_view("Obj"), putils_nameof(Obj));
}

TEST(nameof, nameof_private) {
    EXPECT_EQ(std::string_view("i"), putils_nameof_private(_i));
}