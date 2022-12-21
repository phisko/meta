// gtest
#include <gtest/gtest.h>

// meta
#include "putils/meta/traits/member_function_return_type.hpp"

struct obj {
	float f(int, double);
	float fconst(int, double) const;
	float fnoexcept(int, double) noexcept;
	float fconstnoexcept(int, double) const noexcept;

	int i = 0;
};

template<typename T>
using result = std::is_same<float, putils::member_function_return_type<T>>;

TEST(member_function_return_type, normal) {
	static_assert(result<decltype(&obj::f)>());
	SUCCEED();
}

TEST(member_function_return_type, const) {
	static_assert(result<decltype(&obj::fconst)>());
	SUCCEED();
}

TEST(member_function_return_type, noexcept) {
	static_assert(result<decltype(&obj::fnoexcept)>());
	SUCCEED();
}

TEST(member_function_return_type, const_noexcept) {
	static_assert(result<decltype(&obj::fconstnoexcept)>());
	SUCCEED();
}
