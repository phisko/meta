// gtest
#include <gtest/gtest.h>

// meta
#include "traits/function_return_type.hpp"

// putils
#include "function.hpp"

TEST(function_return_type, function) {
    bool f(int i, double d);
    static_assert(std::is_same<bool, putils::function_return_type<decltype(f)>>());
    SUCCEED();
}

TEST(function_return_type, noexcept) {
    bool g(int i, double d) noexcept;
    static_assert(std::is_same<bool, putils::function_return_type<decltype(g)>>());
    SUCCEED();
}

TEST(function_return_type, std_function) {
    const std::function<bool(int, double)> f;
    static_assert(std::is_same<bool, putils::function_return_type<decltype(f)>>());
    SUCCEED();
}

TEST(function_return_type, putils_function) {
    const putils::function<bool(int, double), 64> f;
    static_assert(std::is_same<bool, putils::function_return_type<decltype(f)>>());
    SUCCEED();
}
