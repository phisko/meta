#include <gtest/gtest.h>
#include "meta/new_from_tuple.hpp"

namespace {
    struct Obj {
        Obj(int i = 0) : i(i) {}

        int i;
    };
}

TEST(new_from_tuple, new_from_tuple) {
    const auto tuple = std::make_tuple(42);
    const auto ptr = putils::new_from_tuple<Obj>(tuple);
    EXPECT_EQ(ptr->i, 42);
}