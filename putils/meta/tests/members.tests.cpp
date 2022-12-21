// gtest
#include <gtest/gtest.h>

// meta
#include "putils/meta/members.hpp"

namespace {
	struct obj {
		double d = 1024;
		int i = 42;
		using member = decltype(&obj::i);
	};
}

TEST(members, member_type) {
	static_assert(std::is_same<int, putils::member_type<obj::member>>());
	SUCCEED();
}

TEST(members, member_type_macro) {
	static_assert(std::is_same<int, PUTILS_MEMBER_TYPE(obj, obj::member)>());
	SUCCEED();
}

TEST(members, object_type) {
	static_assert(std::is_same<obj, putils::object_type<obj::member>>());
	SUCCEED();
}

TEST(members, member_offset) {
	const auto offset = putils::member_offset(&obj::i);
	const obj obj;
	EXPECT_EQ((const char *)&obj + offset, (const char *)&obj.i);
}