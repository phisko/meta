#include <gtest/gtest.h>
#include "function.hpp"
#include "meta/traits/is_function.hpp"

TEST(IsFunctionTest, Function) {
    void f(int i, double d);
    static_assert(putils::is_function<decltype(f)>());
    SUCCEED();
}

TEST(IsFunctionTest, Noexcept) {
    void g(int i, double d) noexcept;
    static_assert(putils::is_function<decltype(g)>());
    SUCCEED();
}

TEST(IsFunctionTest, StdFunction) {
    const std::function<void(int, double)> f;
    static_assert(putils::is_function<decltype(f)>());
    SUCCEED();
}

TEST(IsFunctionTest, PutilsFunction) {
    const putils::function<void(int, double), 64> f;
    static_assert(putils::is_function<decltype(f)>());
    SUCCEED();
}

TEST(IsFunction, False) {
    static_assert(!putils::is_function<int>());
    SUCCEED();
}