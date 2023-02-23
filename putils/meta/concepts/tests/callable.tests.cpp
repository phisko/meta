// gtest
#include <gtest/gtest.h>

// meta
#include "putils/meta/concepts/callable.hpp"

TEST(callable, function) {
	void f(int i, double d);
	static_assert(putils::callable<decltype(f)>);
	SUCCEED();
}

TEST(callable, noexcept) {
	void f(int i, double d) noexcept;
	static_assert(putils::callable<decltype(f)>);
	SUCCEED();
}

TEST(callable, std_function) {
	const std::function<void(int, double)> f;
	static_assert(putils::callable<decltype(f)>);
	SUCCEED();
}

TEST(callable, false) {
	static_assert(!putils::callable<int>);
	SUCCEED();
}