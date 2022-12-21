// gtest
#include <gtest/gtest.h>

// meta
#include "putils/meta/traits/is_member_function_ptr.hpp"

struct obj {
	void f();
	void fnoexcept() noexcept;
	void fconst() const;
	void fconstnoexcept() const noexcept;

	int i = 0;
};

TEST(is_member_function_ptr, normal) {
	static_assert(putils::is_member_function_ptr<decltype(&obj::f)>());
	SUCCEED();
}

TEST(is_member_function_ptr, const) {
	static_assert(putils::is_member_function_ptr<decltype(&obj::fconst)>());
	SUCCEED();
}

TEST(is_member_function_ptr, noexcept) {
	static_assert(putils::is_member_function_ptr<decltype(&obj::fnoexcept)>());
	SUCCEED();
}

TEST(is_member_function_ptr, const_noexcept) {
	static_assert(putils::is_member_function_ptr<decltype(&obj::fconstnoexcept)>());
	SUCCEED();
}

TEST(is_member_function_ptr, attribute) {
	static_assert(!putils::is_member_function_ptr<decltype(&obj::i)>());
	SUCCEED();
}

TEST(is_member_function_ptr, pointer) {
	static_assert(!putils::is_member_function_ptr<int *>());
	SUCCEED();
}

TEST(is_member_function_ptr, function) {
	static_assert(!putils::is_member_function_ptr<void (*)()>());
	SUCCEED();
}
