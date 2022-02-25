#include <gtest/gtest.h>
#include "meta/traits/member_function_decay.hpp"

struct Obj {
    void f(int, double);
    void fconst(int, double) const;
    void fnoexcept(int, double) noexcept;
    void fconstnoexcept(int, double) const noexcept;

    int i = 0;
};

template<typename T>
using Result = std::is_same<void (Obj::*)(int, double), putils::member_function_decay<T>>;

TEST(member_function_decay, normal) {
    static_assert(Result<decltype(&Obj::f)>());
    SUCCEED();
}

TEST(member_function_decay, const) {
    static_assert(Result<decltype(&Obj::fconst)>());
    SUCCEED();
}

TEST(member_function_decay, noexcept) {
    static_assert(Result<decltype(&Obj::fnoexcept)>());
    SUCCEED();
}

TEST(member_function_decay, const_noexcept) {
    static_assert(Result<decltype(&Obj::fconstnoexcept)>());
    SUCCEED();
}
