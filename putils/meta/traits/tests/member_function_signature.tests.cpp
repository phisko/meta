// gtest
#include <gtest/gtest.h>

// meta
#include "putils/meta/traits/member_function_signature.hpp"

struct obj {
    float f(int, double);
    float fconst(int, double) const;
    float fnoexcept(int, double) noexcept;
    float fconstnoexcept(int, double) const noexcept;

    int i = 0;
};

template<typename T>
using result = std::is_same<float(int, double), putils::member_function_signature<T>>;

TEST(member_function_signature, normal) {
    static_assert(result<decltype(&obj::f)>());
    SUCCEED();
}

TEST(member_function_signature, const) {
    static_assert(result<decltype(&obj::fconst)>());
    SUCCEED();
}

TEST(member_function_signature, noexcept) {
    static_assert(result<decltype(&obj::fnoexcept)>());
    SUCCEED();
}

TEST(member_function_signature, const_noexcept) {
    static_assert(result<decltype(&obj::fconstnoexcept)>());
    SUCCEED();
}
