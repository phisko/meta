// gtest
#include <gtest/gtest.h>

// meta
#include "traits/function_signature.hpp"

TEST(function_signature, function) {
    bool f(int i, double d);
    static_assert(std::is_same<bool(*)(int, double), putils::function_signature<decltype(f)>>());
    SUCCEED();
}

TEST(function_signature, noexcept) {
    bool g(int i, double d) noexcept;
    static_assert(std::is_same<bool(*)(int, double), putils::function_signature<decltype(g)>>());
    SUCCEED();
}

TEST(function_signature, std_function) {
    const std::function<bool(int, double)> f;
    static_assert(std::is_same<bool(*)(int, double), putils::function_signature<decltype(f)>>());
    SUCCEED();
}
