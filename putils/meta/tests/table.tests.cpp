// gtest
#include <gtest/gtest.h>

// meta
#include "putils/meta/table.hpp"

class table_constexpr : public ::testing::Test {
	public:
	static constexpr auto table = putils::make_table(
		"string", putils::meta::type<const char *>(),
		"int", putils::meta::type<int>(),
		"float", putils::meta::type<float>());
};

TEST_F(table_constexpr, size) {
	static_assert(std::tuple_size<decltype(table)>() == 3);
	SUCCEED();
}
TEST_F(table_constexpr, size_empty) {
	constexpr auto empty = putils::make_table();
	static_assert(std::tuple_size<decltype(empty)>() == 0);
	SUCCEED();
}

TEST_F(table_constexpr, get_key) {
	constexpr auto string_name = putils::get_key<const char *>(table, putils::meta::type<const char *>());
	static_assert(string_name != nullptr);
	static_assert(*string_name == std::string_view("string"));

	static_assert(*putils::get_key<const char *>(table, putils::meta::type<int>()) == std::string_view("int"));
	static_assert(*putils::get_key<const char *>(table, putils::meta::type<float>()) == std::string_view("float"));
	SUCCEED();
}

TEST_F(table_constexpr, get_key_missing) {
	static_assert(putils::get_key<const char *>(table, putils::meta::type<double>()) == nullptr);
	SUCCEED();
}

TEST_F(table_constexpr, get_key_callback) {
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

TEST_F(table_constexpr, get_key_callback_missing) {
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

TEST_F(table_constexpr, get_value) {
	constexpr auto string_type = putils::get_value<putils::meta::type<const char *>>(table, "string");
	static_assert(std::is_same_v<putils_wrapped_type(*string_type), const char *>);

	constexpr auto int_type = putils::get_value<putils::meta::type<int>>(table, "int");
	static_assert(std::is_same_v<putils_wrapped_type(*int_type), int>);

	constexpr auto float_type = putils::get_value<putils::meta::type<float>>(table, "float");
	static_assert(std::is_same_v<putils_wrapped_type(*float_type), float>);

	SUCCEED();
}

TEST_F(table_constexpr, get_value_missing) {
	static_assert(putils::get_value<putils::meta::type<double>>(table, "double") == nullptr);
	SUCCEED();
}

TEST_F(table_constexpr, get_value_callback) {
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

TEST_F(table_constexpr, get_value_callback_missing) {
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

class table_mutable : public ::testing::Test {
	public:
	void SetUp() override {
		table = putils::make_table(42, false);
	}

	putils::table<std::pair<int, bool>> table;
};

TEST_F(table_mutable, get_key) {
	*putils::get_key<int>(table, false) = 84;
	EXPECT_EQ(std::get<0>(table).first, 84);
}

TEST_F(table_mutable, get_key_missing) {
	EXPECT_EQ(putils::get_key<float>(table, true), nullptr);
}

TEST_F(table_mutable, get_key_callback) {
	putils::get_key(table, false, [](int & key) {
		key = 84;
	});
	EXPECT_EQ(std::get<0>(table).first, 84);
}

TEST_F(table_mutable, get_key_callback_missing) {
	bool found = false;
	putils::get_key(table, 42, [&](auto && key) {
		found = true;
	});
	EXPECT_FALSE(found);
}

TEST_F(table_mutable, get_value) {
	*putils::get_value<bool>(table, 42) = true;
	EXPECT_EQ(std::get<0>(table).second, true);
}

TEST_F(table_mutable, get_value_missing) {
	EXPECT_EQ(putils::get_value<float>(table, true), nullptr);
}

TEST_F(table_mutable, get_value_callback) {
	putils::get_value(table, 42, [](bool & value) {
		value = true;
	});
	EXPECT_EQ(std::get<0>(table).second, true);
}

TEST_F(table_mutable, get_value_callback_missing) {
	bool found = false;
	putils::get_value(table, "foo", [&](auto && value) {
		found = true;
	});
	EXPECT_FALSE(found);
}