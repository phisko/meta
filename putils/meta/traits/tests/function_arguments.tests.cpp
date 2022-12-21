// gtest
#include <gtest/gtest.h>

// meta
#include "putils/meta/traits/function_arguments.hpp"

TEST(function_arguments, function) {
	void f(int i, double d);
	static_assert(std::is_same<std::tuple<int, double>, putils::function_arguments<decltype(f)>>());
	SUCCEED();
}

TEST(function_arguments, noexcept) {
	void g(int i, double d) noexcept;
	static_assert(std::is_same<std::tuple<int, double>, putils::function_arguments<decltype(g)>>());
	SUCCEED();
}

TEST(function_arguments, std_function) {
	const std::function<void(int, double)> f;
	static_assert(std::is_same<std::tuple<int, double>, putils::function_arguments<decltype(f)>>());
	SUCCEED();
}
