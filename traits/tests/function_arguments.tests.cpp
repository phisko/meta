#include <gtest/gtest.h>
#include "function.hpp"
#include "meta/traits/function_arguments.hpp"

TEST(FunctionArgumentsTest, Function) {
    void f(int i, double d);
    static_assert(std::is_same<std::tuple<int, double>, putils::function_arguments<decltype(f)>>());
    SUCCEED();
}

TEST(FunctionArgumentsTest, Noexcept) {
    void g(int i, double d) noexcept;
    static_assert(std::is_same<std::tuple<int, double>, putils::function_arguments<decltype(g)>>());
    SUCCEED();
}

TEST(FunctionArgumentsTest, StdFunction) {
    const std::function<void(int, double)> f;
    static_assert(std::is_same<std::tuple<int, double>, putils::function_arguments<decltype(f)>>());
    SUCCEED();
}

TEST(FunctionArgumentsTest, PutilsFunction) {
    const putils::function<void(int, double), 64> f;
    static_assert(std::is_same<std::tuple<int, double>, putils::function_arguments<decltype(f)>>());
    SUCCEED();
}
