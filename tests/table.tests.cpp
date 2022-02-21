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

TEST_F(ConstexprTableTest, Size) {
    static_assert(std::tuple_size<decltype(table)>() == 3);
    SUCCEED();
}
TEST_F(ConstexprTableTest, EmptySize) {
    constexpr auto empty = putils::make_table();
    static_assert(std::tuple_size<decltype(empty)>() == 0);
    SUCCEED();
}

TEST_F(ConstexprTableTest, GetKeyValue) {
    constexpr auto stringName = putils::get_key<const char *>(table, putils::meta::type<const char *>());
    static_assert(stringName != nullptr);
    static_assert(*stringName == std::string_view("string"));

    static_assert(*putils::get_key<const char *>(table, putils::meta::type<int>()) == std::string_view("int"));
    static_assert(*putils::get_key<const char *>(table, putils::meta::type<float>()) == std::string_view("float"));
    SUCCEED();
}

TEST_F(ConstexprTableTest, GetMissingKeyValue) {
    static_assert(putils::get_key<const char *>(table, putils::meta::type<double>()) == nullptr);
    SUCCEED();
}

TEST_F(ConstexprTableTest, GetKeyCallback) {
    constexpr auto ret = [] {
        bool ret = true;

        putils::get_key(table, putils::meta::type<const char *>(), [&](auto && key) {
            ret &= key == std::string_view("string");
        });

        putils::get_key(table, putils::meta::type<int>(), [&](auto && key) {
            ret &= key == std::string_view("int");
        });

        putils::get_key(table, putils::meta::type<float>(), [&](auto && key) {
            ret &= key == std::string_view("float");
        });

        return ret;
    }();
    static_assert(ret);
    SUCCEED();
}

TEST_F(ConstexprTableTest, GetMissingKeyCallback) {
    constexpr auto ret = [] {
        bool found = false;
        putils::get_key(table, "foo", [&](auto &&) {
            found = true;
        });
        return !found;
    };
    static_assert(ret);
    SUCCEED();
}

TEST_F(ConstexprTableTest, GetValueValue) {
    constexpr auto stringType = putils::get_value<putils::meta::type<const char *>>(table, "string");
    static_assert(std::is_same_v<putils_wrapped_type(*stringType), const char *>);

    constexpr auto intType = putils::get_value<putils::meta::type<int>>(table, "int");
    static_assert(std::is_same_v<putils_wrapped_type(*intType), int>);

    constexpr auto floatType = putils::get_value<putils::meta::type<float>>(table, "float");
    static_assert(std::is_same_v<putils_wrapped_type(*floatType), float>);

    SUCCEED();
}

TEST_F(ConstexprTableTest, GetMissingValueValue) {
    static_assert(putils::get_value<putils::meta::type<double>>(table, "double") == nullptr);
    SUCCEED();
}

TEST_F(ConstexprTableTest, GetValueCallback) {
    constexpr auto ret = [] {
        bool ret = true;

        putils::get_value(table, "string", [&](auto && key) {
            ret &= std::is_same_v<putils_wrapped_type(key), const char *>;
        });

        putils::get_value(table, "int", [&](auto && key) {
            ret &= std::is_same_v<putils_wrapped_type(key), int>;
        });

        putils::get_value(table, "float", [&](auto && key) {
            ret &= std::is_same_v<putils_wrapped_type(key), float>;
        });

        return ret;
    }();

    static_assert(ret);
    SUCCEED();
}

TEST_F(ConstexprTableTest, GetMissingValueCallback) {
    constexpr auto ret = [] {
        bool found = false;
        putils::get_value(table, "foo", [&](auto &&) {
            found = true;
        });
        return !found;
    };
    static_assert(ret);
    SUCCEED();
}

class MutableTableTest : public ::testing::Test {
public:
    void SetUp() override {
        table = putils::make_table(42, false);
    }

    putils::table<std::pair<int, bool>> table;
};

TEST_F(MutableTableTest, GetKeyCallback) {
    putils::get_key(table, false, [](int & key) {
        key = 84;
    });
    EXPECT_EQ(std::get<0>(table).first, 84);
}

TEST_F(MutableTableTest, GetMissingKeyCallback) {
    bool found = false;
    putils::get_key(table, 42, [&](auto && key) {
        found = true;
    });
    EXPECT_FALSE(found);
}

TEST_F(MutableTableTest, GetKeyValue) {
    *putils::get_key<int>(table, false) = 84;
    EXPECT_EQ(std::get<0>(table).first, 84);
}

TEST_F(MutableTableTest, GetMissingKeyValue) {
    EXPECT_EQ(putils::get_key<float>(table, true), nullptr);
}

TEST_F(MutableTableTest, GetValueCallback) {
    putils::get_value(table, 42, [](bool & value) {
        value = true;
    });
    EXPECT_EQ(std::get<0>(table).second, true);
}

TEST_F(MutableTableTest, GetMissingValueCallback) {
    bool found = false;
    putils::get_value(table, "foo", [&](auto && value) {
        found = true;
    });
    EXPECT_FALSE(found);
}

TEST_F(MutableTableTest, GetValueValue) {
    *putils::get_value<bool>(table, 42) = true;
    EXPECT_EQ(std::get<0>(table).second, true);
}

TEST_F(MutableTableTest, GetMissingValueValue) {
    EXPECT_EQ(putils::get_value<float>(table, true), nullptr);
}