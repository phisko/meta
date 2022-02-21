#include <gtest/gtest.h>
#include "meta/traits/member_function_return_type.hpp"

struct Obj {
    float f(int, double);
    float fconst(int, double) const;
    float fnoexcept(int, double) noexcept;
    float fconstnoexcept(int, double) const noexcept;

    int i = 0;
};

template<typename T>
using Result = std::is_same<float, putils::member_function_return_type<T>>;

TEST(MemberFunctionReturnTypeTest, Normal) {
    static_assert(Result<decltype(&Obj::f)>());
    SUCCEED();
}

TEST(MemberFunctionReturnTypeTest, Const) {
    static_assert(Result<decltype(&Obj::fconst)>());
    SUCCEED();
}

TEST(MemberFunctionReturnTypeTest, Noexcept) {
    static_assert(Result<decltype(&Obj::fnoexcept)>());
    SUCCEED();
}

TEST(MemberFunctionReturnTypeTest, ConstNoexcept) {
    static_assert(Result<decltype(&Obj::fconstnoexcept)>());
    SUCCEED();
}
