#include <gtest/gtest.h>
#include "meta/apply.hpp"

static int func(int i) {
    return i;
}

TEST(ApplyTest, Function) {
    EXPECT_EQ(putils::apply(std::make_tuple(42), func), 42);
}

TEST(ApplyTest, Lambda) {
    const auto func = [](int i) {
        return i;
    };
    EXPECT_EQ(putils::apply(std::make_tuple(42), func), 42);
}

TEST(ApplyTest, Modify) {
    auto tuple = std::make_tuple(42);
    const auto func = [](int & i) {
        i = 0;
    };
    putils::apply(tuple, func);
    EXPECT_EQ(std::get<0>(tuple), 0);
}