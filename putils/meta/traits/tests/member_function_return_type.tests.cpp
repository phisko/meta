// gtest
#include <gtest/gtest.h>

// meta
#include "traits/member_function_return_type.hpp"

struct Obj {
    float f(int, double);
    float fconst(int, double) const;
    float fnoexcept(int, double) noexcept;
    float fconstnoexcept(int, double) const noexcept;

    int i = 0;
};

template<typename T>
using Result = std::is_same<float, putils::member_function_return_type<T>>;

TEST(member_function_return_type, normal) {
    static_assert(Result<decltype(&Obj::f)>());
    SUCCEED();
}

TEST(member_function_return_type, const) {
    static_assert(Result<decltype(&Obj::fconst)>());
    SUCCEED();
}

TEST(member_function_return_type, noexcept) {
    static_assert(Result<decltype(&Obj::fnoexcept)>());
    SUCCEED();
}

TEST(member_function_return_type, const_noexcept) {
    static_assert(Result<decltype(&Obj::fconstnoexcept)>());
    SUCCEED();
}
