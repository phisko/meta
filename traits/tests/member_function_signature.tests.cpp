#include <gtest/gtest.h>
#include "meta/traits/member_function_signature.hpp"

struct Obj {
    float f(int, double);
    float fconst(int, double) const;
    float fnoexcept(int, double) noexcept;
    float fconstnoexcept(int, double) const noexcept;

    int i = 0;
};

template<typename T>
using Result = std::is_same<float(int, double), putils::member_function_signature<T>>;

TEST(MemberFunctionSignatureTest, Normal) {
    static_assert(Result<decltype(&Obj::f)>());
    SUCCEED();
}

TEST(MemberFunctionSignatureTest, Const) {
    static_assert(Result<decltype(&Obj::fconst)>());
    SUCCEED();
}

TEST(MemberFunctionSignatureTest, Noexcept) {
    static_assert(Result<decltype(&Obj::fnoexcept)>());
    SUCCEED();
}

TEST(MemberFunctionSignatureTest, ConstNoexcept) {
    static_assert(Result<decltype(&Obj::fconstnoexcept)>());
    SUCCEED();
}
