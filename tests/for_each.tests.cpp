#include <gtest/gtest.h>
#include "meta/for_each.hpp"
#include "meta/table.hpp"

TEST(ForEachTest, ForEachType) {
    auto table = putils::make_table(
        putils::meta::type<int>(), false,
        putils::meta::type<double>(), false
    );

    putils::for_each_type<int, double>([&](auto && t) {
        const auto value = putils::get_value<bool>(table, t);
        EXPECT_NE(value, nullptr);
        *value = true;
    });

    EXPECT_TRUE(std::get<0>(table).second);
    EXPECT_TRUE(std::get<1>(table).second);
}

TEST(ForEachTest, TupleForEach) {
    std::stringstream s;

    const auto tuple = std::make_tuple(42, false);
    putils::tuple_for_each(tuple, [&](auto && obj) {
        s << obj;
    });
    EXPECT_EQ(s.str(), "420");
}

TEST(ForEachTest, TupleForEachMutate) {
    auto tuple = std::make_tuple(42, true);
    putils::tuple_for_each(tuple, [&](auto && obj) {
        obj = 0;
    });
    EXPECT_EQ(std::get<0>(tuple), 0);
    EXPECT_EQ(std::get<1>(tuple), false);
}