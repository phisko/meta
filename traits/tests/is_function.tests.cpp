#include <gtest/gtest.h>
#include "function.hpp"
#include "meta/traits/is_function.hpp"

TEST(is_function, function) {
    void f(int i, double d);
    static_assert(putils::is_function<decltype(f)>());
    SUCCEED();
}

TEST(is_function, noexcept) {
    void g(int i, double d) noexcept;
    static_assert(putils::is_function<decltype(g)>());
    SUCCEED();
}

TEST(is_function, std_function) {
    const std::function<void(int, double)> f;
    static_assert(putils::is_function<decltype(f)>());
    SUCCEED();
}

TEST(is_function, putils_function) {
    const putils::function<void(int, double), 64> f;
    static_assert(putils::is_function<decltype(f)>());
    SUCCEED();
}

TEST(is_function, false) {
    static_assert(!putils::is_function<int>());
    SUCCEED();
}