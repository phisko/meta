#include <gtest/gtest.h>
#include "meta/table.hpp"

class ConstexprTableTest : public ::testing::Test {
public:
    static constexpr auto table = putils::make_table(
        "string", putils::meta::type<const char *>(),
        "int", putils::meta::type<int>(),
        "float", putils::meta::type<float>()
    );
};

TEST_F(ConstexprTableTest, EmptySize) {
    constexpr auto empty = putils::make_table();
    static_assert(std::tuple_size<decltype(empty)>() == 0);
    SUCCEED();
}

TEST_F(ConstexprTableTest, Size) {
    static_assert(std::tuple_size<decltype(table)>() == 3);
    SUCCEED();
}

TEST_F(ConstexprTableTest, HasKeyTrue) {
    static_assert(putils::has_key(table, "string"));
    SUCCEED();
}

TEST_F(ConstexprTableTest, HasKeyFalse) {
    static_assert(!putils::has_key(table, "foo"));
    SUCCEED();
}

TEST_F(ConstexprTableTest, HasValueTrue) {
    static_assert(putils::has_value(table, putils::meta::type<int>()));
    SUCCEED();
}

TEST_F(ConstexprTableTest, HasValueFalse) {
    static_assert(!putils::has_value(table, "foo"));
    SUCCEED();
}

TEST_F(ConstexprTableTest, GetKeyCallback) {
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

TEST_F(ConstexprTableTest, TryGetKeyCallback) {
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

TEST_F(ConstexprTableTest, GetKeyValue) {
    constexpr auto & key = putils::get_key<const char *>(table, putils::meta::type<const char *>());
    static_assert(key == std::string_view("string"));
    SUCCEED();
}

TEST_F(ConstexprTableTest, TryGetKeyValue) {
    constexpr auto & key = *putils::try_get_key<const char *>(table, putils::meta::type<const char *>());
    static_assert(key == std::string_view("string"));
    SUCCEED();
}

TEST_F(ConstexprTableTest, GetValueCallback) {
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

TEST_F(ConstexprTableTest, TryGetValueCallback) {
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

TEST_F(ConstexprTableTest, GetValueValue) {
    constexpr auto & type = putils::get_value<putils::meta::type<int>>(table, "int");
    static_assert(std::is_same_v<putils_wrapped_type(type), int>);
    SUCCEED();
}

TEST_F(ConstexprTableTest, TryGetValueValue) {
    constexpr auto & type = *putils::try_get_value<putils::meta::type<int>>(table, "int");
    static_assert(std::is_same_v<putils_wrapped_type(type), int>);
    SUCCEED();
}

TEST_F(ConstexprTableTest, GetMissingKey) {
    ASSERT_DEATH({
        putils::get_key(table, "foo", [](auto &&) {});
    }, "Key not found");
}

TEST_F(ConstexprTableTest, TryGetMissingKey) {
    bool ret = true;
    putils::try_get_key(table, "foo", [&](auto &&) {
        ret = false;
    });
    EXPECT_TRUE(ret);
}

TEST_F(ConstexprTableTest, GetMissingValue) {
    ASSERT_DEATH({
        putils::get_value(table, "foo", [](auto &&){});
    }, "Key not found");
}

TEST_F(ConstexprTableTest, TryGetMissingValue) {
    bool ret = true;
    putils::try_get_value(table, "foo", [&](auto &&) {
        ret = false;
    });
    EXPECT_TRUE(ret);
}

class MutableTableTest : public ::testing::Test {
public:
    void SetUp() override {
        table = putils::make_table(42, false);
    }

    putils::table<std::pair<int, bool>> table = putils::make_table(42, false);
};

TEST_F(MutableTableTest, GetKeyCallback) {
    putils::get_key(table, false, [](int & key) {
        key = 84;
    });
    EXPECT_EQ(std::get<0>(table).first, 84);
}

TEST_F(MutableTableTest, TryGetKeyCallback) {
    putils::try_get_key(table, false, [](int & key) {
        key = 84;
    });
    EXPECT_EQ(std::get<0>(table).first, 84);
}

TEST_F(MutableTableTest, GetKeyValue) {
    putils::get_key<int>(table, false) = 84;
    EXPECT_EQ(std::get<0>(table).first, 84);
}

TEST_F(MutableTableTest, TryGetKeyValue) {
    *putils::try_get_key<int>(table, false) = 84;
    EXPECT_EQ(std::get<0>(table).first, 84);
}

TEST_F(MutableTableTest, GetValueCallback) {
    putils::get_value(table, 42, [](bool & value) {
        value = true;
    });
    EXPECT_EQ(std::get<0>(table).second, true);
}

TEST_F(MutableTableTest, TryGetValueCallback) {
    putils::try_get_value(table, 42, [](bool & value) {
        value = true;
    });
    EXPECT_EQ(std::get<0>(table).second, true);
}

TEST_F(MutableTableTest, GetValueValue) {
    putils::get_value<bool>(table, 42) = true;
    EXPECT_EQ(std::get<0>(table).second, true);
}

TEST_F(MutableTableTest, TryGetValueValue) {
    *putils::try_get_value<bool>(table, 42) = true;
    EXPECT_EQ(std::get<0>(table).second, true);
}
