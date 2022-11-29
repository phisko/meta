// gtest
#include <gtest/gtest.h>

// meta
#include "putils/meta/for_each.hpp"
#include "putils/meta/table.hpp"

TEST(for_each, for_each_type_constexpr) {
    putils::for_each_type<int, double>([](auto && t) {
        static_assert(std::is_same<putils_wrapped_type(t), int>() || std::is_same<putils_wrapped_type(t), double>());
    });
    SUCCEED();
}

TEST(for_each, for_each_type) {
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

TEST(for_each, for_each_type_constexpr_return_bool) {
    constexpr auto ret = putils::for_each_type<int, double>([](auto && t) {
        static_assert(std::is_same<putils_wrapped_type(t), int>() || std::is_same<putils_wrapped_type(t), double>());
        return true;
    });
    static_assert(ret);

    constexpr auto bad = putils::for_each_type<int, double>([](auto && t) {
        return false;
    });
    static_assert(!bad);
    SUCCEED();
}

TEST(for_each, for_each_type_return_bool) {
    auto table = putils::make_table(
        putils::meta::type<int>(), false,
        putils::meta::type<double>(), false,
        putils::meta::type<float>(), false
    );

    const auto ret = putils::for_each_type<int, double>([&](auto && t) -> bool {
        const auto value = putils::get_value<bool>(table, t);
        EXPECT_NE(value, nullptr);
        *value = true;
        return std::is_same<putils_wrapped_type(t), double>();
    });

    EXPECT_TRUE(ret);

    EXPECT_TRUE(std::get<0>(table).second);
    EXPECT_TRUE(std::get<1>(table).second);
    EXPECT_FALSE(std::get<2>(table).second);
}

TEST(for_each, for_each_type_constexpr_return_optional) {
    constexpr auto ret = putils::for_each_type<int, double>([](auto && t) {
        static_assert(std::is_same<putils_wrapped_type(t), int>() || std::is_same<putils_wrapped_type(t), double>());
        return std::optional<int>(42);
    });
    static_assert(*ret == 42);

    constexpr auto bad = putils::for_each_type<int, double>([](auto && t) -> std::optional<int> {
        return std::nullopt;
    });
    static_assert(bad == std::nullopt);
    SUCCEED();
}

TEST(for_each, for_each_type_return_optional) {
    auto table = putils::make_table(
        putils::meta::type<int>(), false,
        putils::meta::type<double>(), false,
        putils::meta::type<float>(), false
    );

    int counter = 0;
    const auto ret = putils::for_each_type<int, double>([&](auto && t) -> std::optional<int> {
        const auto value = putils::get_value<bool>(table, t);
        EXPECT_NE(value, nullptr);
        *value = true;
        ++counter;
        if (std::is_same<putils_wrapped_type(t), double>())
            return counter;
        return std::nullopt;
    });

    EXPECT_EQ(counter, 2);
    EXPECT_EQ(ret, counter);

    EXPECT_TRUE(std::get<0>(table).second);
    EXPECT_TRUE(std::get<1>(table).second);
    EXPECT_FALSE(std::get<2>(table).second);
}

TEST(for_each, tuple_for_each_constexpr) {
    constexpr auto ret = [] {
        int total = 0;
        const auto tuple = std::make_tuple(42, 42);
        putils::tuple_for_each(tuple, [&](auto && obj) {
            total += obj;
        });
        return total;
    }();
    static_assert(ret == 84);
}

TEST(for_each, tuple_for_each) {
    std::stringstream s;

    const auto tuple = std::make_tuple(42, false);
    putils::tuple_for_each(tuple, [&](auto && obj) {
        s << obj;
    });
    EXPECT_EQ(s.str(), "420");
}

TEST(for_each, tuple_for_each_constexpr_return_bool) {
    constexpr auto ret = [] {
        std::pair<bool, int> true_and_84;

        int total = 0;

        const auto tuple = std::make_tuple(42, 42, 42);
        const auto ret = putils::tuple_for_each(tuple, [&](auto && obj) {
            total += obj;
            if (total == 84)
                return true;
            return false;
        });

        true_and_84.first = ret;
        true_and_84.second = total;
        return true_and_84;
    }();

    static_assert(ret.first == true);
    static_assert(ret.second == 84);
}

TEST(for_each, tuple_for_each_return_bool) {
    int total = 0;

    const auto tuple = std::make_tuple(42, 42, 42);
    const auto ret = putils::tuple_for_each(tuple, [&](auto && obj) {
        total += obj;
        if (total == 84)
            return true;
        return false;
    });

    EXPECT_EQ(total, 84);
    EXPECT_TRUE(ret);
}

TEST(for_each, tuple_for_each_constexpr_return_optional) {
    constexpr auto ret = [] {
        std::pair<int, int> pair_84_and_42;

        int total = 0;

        const auto tuple = std::make_tuple(42, 42, 42);
        const auto ret = putils::tuple_for_each(tuple, [&](auto && obj) -> std::optional<int> {
            total += obj;
            if (total == 84)
                return 42;
            return std::nullopt;
        });

        pair_84_and_42.first = total;
        pair_84_and_42.second = *ret;
        return pair_84_and_42;
    }();

    static_assert(ret.first == 84);
    static_assert(ret.second == 42);
}

TEST(for_each, tuple_for_each_return_optional) {
    int total = 0;

    const auto tuple = std::make_tuple(42, 42, 42);
    const auto ret = putils::tuple_for_each(tuple, [&](auto && obj) -> std::optional<int> {
        total += obj;
        if (total == 84)
            return 42;
        return std::nullopt;
    });

    EXPECT_EQ(total, 84);
    EXPECT_EQ(ret, 42);
}

TEST(for_each, tuple_for_each_mutate) {
    auto tuple = std::make_tuple(42, true);
    putils::tuple_for_each(tuple, [&](auto && obj) {
        obj = 0;
    });
    EXPECT_EQ(std::get<0>(tuple), 0);
    EXPECT_EQ(std::get<1>(tuple), false);
}