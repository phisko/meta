#include <gtest/gtest.h>
#include "meta/table.hpp"

class TableTest : public ::testing::Test {
public:
    static constexpr auto table = putils::make_table(
        "string", putils::meta::type<const char *>(),
        "int", putils::meta::type<int>(),
        "float", putils::meta::type<float>()
    );
};

TEST_F(TableTest, EmptySize) {
    constexpr auto empty = putils::make_table();
    static_assert(std::tuple_size<decltype(empty)>() == 0);
    SUCCEED();
}

TEST_F(TableTest, Size) {
    static_assert(std::tuple_size<decltype(table)>() == 3);
    SUCCEED();
}

TEST_F(TableTest, HasKeyTrue) {
    static_assert(putils::has_key(table, "string"));
    SUCCEED();
}

TEST_F(TableTest, HasKeyFalse) {
    static_assert(!putils::has_key(table, "foo"));
    SUCCEED();
}

TEST_F(TableTest, HasValueTrue) {
    static_assert(putils::has_value(table, putils::meta::type<int>()));
    SUCCEED();
}

TEST_F(TableTest, HasValueFalse) {
    static_assert(!putils::has_value(table, "foo"));
    SUCCEED();
}

TEST_F(TableTest, GetKeyCallback) {
    constexpr auto ret = [] {
        bool ret = false;
        putils::get_key(table, putils::meta::type<const char *>(), [&](auto && key) {
            ret = key == std::string_view("string");
        });
        return ret;
    }();
    static_assert(ret);
    SUCCEED();
}

TEST_F(TableTest, TryGetKeyCallback) {
    constexpr auto ret = [] {
        bool ret = false;
        putils::get_key(table, putils::meta::type<const char *>(), [&](auto && key) {
            ret = key == std::string_view("string");
        });
        return ret;
    }();
    static_assert(ret);
    SUCCEED();
}

TEST_F(TableTest, GetKeyValue) {
    constexpr auto & key = putils::get_key<const char *>(table, putils::meta::type<const char *>());
    static_assert(key == std::string_view("string"));
    SUCCEED();
}

TEST_F(TableTest, TryGetKeyValue) {
    constexpr auto & key = *putils::try_get_key<const char *>(table, putils::meta::type<const char *>());
    static_assert(key == std::string_view("string"));
    SUCCEED();
}

TEST_F(TableTest, GetValueCallback) {
    constexpr auto ret = [] {
        bool ret = false;
        putils::get_value(table, "int", [&](auto && t) {
            using Type = putils_wrapped_type(t);
            ret = std::is_same_v<Type, int>;
        });
        return ret;
    };
    static_assert(ret);
    SUCCEED();
}

TEST_F(TableTest, TryGetValueCallback) {
    constexpr auto ret = [] {
        bool ret = false;
        putils::try_get_value(table, "int", [&](auto && t) {
            using Type = putils_wrapped_type(t);
            ret = std::is_same_v<Type, int>;
        });
        return ret;
    };
    static_assert(ret);
    SUCCEED();
}

TEST_F(TableTest, GetValueValue) {
    constexpr auto & type = putils::get_value<putils::meta::type<int>>(table, "int");
    static_assert(std::is_same_v<putils_wrapped_type(type), int>);
    SUCCEED();
}

TEST_F(TableTest, TryGetValueValue) {
    constexpr auto & type = *putils::try_get_value<putils::meta::type<int>>(table, "int");
    static_assert(std::is_same_v<putils_wrapped_type(type), int>);
    SUCCEED();
}

TEST_F(TableTest, GetMissingKey) {
    ASSERT_DEATH({
        putils::get_key(table, "foo", [](auto &&) {});
    }, "Key not found");
}

TEST_F(TableTest, TryGetMissingKey) {
    bool ret = true;
    putils::try_get_key(table, "foo", [&](auto &&) {
        ret = false;
    });
    EXPECT_TRUE(ret);
}

TEST_F(TableTest, GetMissingValue) {
    ASSERT_DEATH({
        putils::get_value(table, "foo", [](auto &&){});
    }, "Key not found");
}

TEST_F(TableTest, TryGetMissingValue) {
    bool ret = true;
    putils::try_get_value(table, "foo", [&](auto &&) {
        ret = false;
    });
    EXPECT_TRUE(ret);
}