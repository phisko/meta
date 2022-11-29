// gtest
#include <gtest/gtest.h>

// meta
#include "putils/meta/traits/member_function_decay.hpp"

struct obj {
    void f(int, double);
    void fconst(int, double) const;
    void fnoexcept(int, double) noexcept;
    void fconstnoexcept(int, double) const noexcept;

    int i = 0;
};

template<typename T>
using result = std::is_same<void (obj::*)(int, double), putils::member_function_decay<T>>;

TEST(member_function_decay, normal) {
    static_assert(result<decltype(&obj::f)>());
    SUCCEED();
}

TEST(member_function_decay, const) {
    static_assert(result<decltype(&obj::fconst)>());
    SUCCEED();
}

TEST(member_function_decay, noexcept) {
    static_assert(result<decltype(&obj::fnoexcept)>());
    SUCCEED();
}

TEST(member_function_decay, const_noexcept) {
    static_assert(result<decltype(&obj::fconstnoexcept)>());
    SUCCEED();
}
