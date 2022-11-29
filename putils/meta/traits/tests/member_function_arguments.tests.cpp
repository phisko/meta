// gtest
#include <gtest/gtest.h>

// meta
#include "putils/meta/traits/member_function_arguments.hpp"

struct obj {
    void f(int, double);
    void fconst(int, double) const;
    void fnoexcept(int, double) noexcept;
    void fconstnoexcept(int, double) const noexcept;

    int i = 0;
};

template<typename T>
using result = std::is_same<std::tuple<int, double>, putils::member_function_arguments<T>>;

TEST(member_function_arguments, normal) {
    static_assert(result<decltype(&obj::f)>());
    SUCCEED();
}

TEST(member_function_arguments, const) {
    static_assert(result<decltype(&obj::fconst)>());
    SUCCEED();
}

TEST(member_function_arguments, noexcept) {
    static_assert(result<decltype(&obj::fnoexcept)>());
    SUCCEED();
}

TEST(member_function_arguments, const_noexcept) {
    static_assert(result<decltype(&obj::fconstnoexcept)>());
    SUCCEED();
}