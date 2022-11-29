// gtest
#include <gtest/gtest.h>

// meta
#include "putils/meta/nameof.hpp"

struct obj {
    int _i = 42;
};

TEST(nameof, nameof) {
    EXPECT_EQ(std::string_view("obj"), putils_nameof(obj));
}

TEST(nameof, nameof_private) {
    EXPECT_EQ(std::string_view("i"), putils_nameof_private(_i));
}