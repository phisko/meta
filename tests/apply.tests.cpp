// gtest
#include <gtest/gtest.h>

// meta
#include "apply.hpp"

static int func(int i) {
    return i;
}

TEST(apply, function) {
    EXPECT_EQ(putils::apply(std::make_tuple(42), func), 42);
}

TEST(apply, lambda) {
    const auto func = [](int i) {
        return i;
    };
    EXPECT_EQ(putils::apply(std::make_tuple(42), func), 42);
}

TEST(apply, modify) {
    auto tuple = std::make_tuple(42);
    const auto func = [](int & i) {
        i = 0;
    };
    putils::apply(tuple, func);
    EXPECT_EQ(std::get<0>(tuple), 0);
}