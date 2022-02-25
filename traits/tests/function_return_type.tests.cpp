#include <gtest/gtest.h>
#include "function.hpp"
#include "meta/traits/function_return_type.hpp"

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
