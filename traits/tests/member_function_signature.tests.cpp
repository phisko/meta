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

TEST(member_function_signature, normal) {
    static_assert(Result<decltype(&Obj::f)>());
    SUCCEED();
}

TEST(member_function_signature, const) {
    static_assert(Result<decltype(&Obj::fconst)>());
    SUCCEED();
}

TEST(member_function_signature, noexcept) {
    static_assert(Result<decltype(&Obj::fnoexcept)>());
    SUCCEED();
}

TEST(member_function_signature, const_noexcept) {
    static_assert(Result<decltype(&Obj::fconstnoexcept)>());
    SUCCEED();
}
