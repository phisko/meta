// gtest
#include <gtest/gtest.h>

// meta
#include "traits/member_function_arguments.hpp"

struct Obj {
    void f(int, double);
    void fconst(int, double) const;
    void fnoexcept(int, double) noexcept;
    void fconstnoexcept(int, double) const noexcept;

    int i = 0;
};

template<typename T>
using Result = std::is_same<std::tuple<int, double>, putils::member_function_arguments<T>>;

TEST(member_function_arguments, normal) {
    static_assert(Result<decltype(&Obj::f)>());
    SUCCEED();
}

TEST(member_function_arguments, const) {
    static_assert(Result<decltype(&Obj::fconst)>());
    SUCCEED();
}

TEST(member_function_arguments, noexcept) {
    static_assert(Result<decltype(&Obj::fnoexcept)>());
    SUCCEED();
}

TEST(member_function_arguments, const_noexcept) {
    static_assert(Result<decltype(&Obj::fconstnoexcept)>());
    SUCCEED();
}