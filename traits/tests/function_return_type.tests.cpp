#include <gtest/gtest.h>
#include "function.hpp"
#include "meta/traits/function_return_type.hpp"

TEST(FunctionReturnTypeTest, Function) {
    bool f(int i, double d);
    static_assert(std::is_same<bool, putils::function_return_type<decltype(f)>>());
    SUCCEED();
}

TEST(FunctionReturnTypeTest, Noexcept) {
    bool g(int i, double d) noexcept;
    static_assert(std::is_same<bool, putils::function_return_type<decltype(g)>>());
    SUCCEED();
}

TEST(FunctionReturnTypeTest, StdFunction) {
    const std::function<bool(int, double)> f;
    static_assert(std::is_same<bool, putils::function_return_type<decltype(f)>>());
    SUCCEED();
}

TEST(FunctionReturnTypeTest, PutilsFunction) {
    const putils::function<bool(int, double), 64> f;
    static_assert(std::is_same<bool, putils::function_return_type<decltype(f)>>());
    SUCCEED();
}
