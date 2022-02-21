#include <gtest/gtest.h>
#include "function.hpp"
#include "meta/traits/function_signature.hpp"

TEST(FunctionSignatureTest, Function) {
    bool f(int i, double d);
    static_assert(std::is_same<bool(*)(int, double), putils::function_signature<decltype(f)>>());
    SUCCEED();
}

TEST(FunctionSignatureTest, Noexcept) {
    bool g(int i, double d) noexcept;
    static_assert(std::is_same<bool(*)(int, double), putils::function_signature<decltype(g)>>());
    SUCCEED();
}

TEST(FunctionSignatureTest, StdFunction) {
    const std::function<bool(int, double)> f;
    static_assert(std::is_same<bool(*)(int, double), putils::function_signature<decltype(f)>>());
    SUCCEED();
}

TEST(FunctionSignatureTest, PutilsFunction) {
    const putils::function<bool(int, double), 64> f;
    static_assert(std::is_same<bool(*)(int, double), putils::function_signature<decltype(f)>>());
    SUCCEED();
}
