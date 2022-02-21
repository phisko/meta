#include <gtest/gtest.h>
#include "meta/traits/member_function_arguments.hpp"

struct Obj {
    void f(int, double);
    void fconst(int, double) const;
    void fnoexcept(int, double) noexcept;
    void fconstnoexcept(int, double) const noexcept;

    int i = 0;
};

template<typename T>
using Result = std::is_same<std::tuple<int, double>, putils::member_function_arguments<T>>;

TEST(MemberFunctionArgumentsTest, Normal) {
    static_assert(Result<decltype(&Obj::f)>());
    SUCCEED();
}

TEST(MemberFunctionArgumentsTest, Const) {
    static_assert(Result<decltype(&Obj::fconst)>());
    SUCCEED();
}

TEST(MemberFunctionArgumentsTest, Noexcept) {
    static_assert(Result<decltype(&Obj::fnoexcept)>());
    SUCCEED();
}

TEST(MemberFunctionArgumentsTest, ConstNoexcept) {
    static_assert(Result<decltype(&Obj::fconstnoexcept)>());
    SUCCEED();
}