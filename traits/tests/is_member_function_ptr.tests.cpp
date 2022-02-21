#include <gtest/gtest.h>
#include "meta/traits/is_member_function_ptr.hpp"

struct Obj {
    void f();
    void fnoexcept() noexcept;
    void fconst() const;
    void fconstnoexcept() const noexcept;

    int i = 0;
};

TEST(IsMemberFunctionPtrTest, Normal) {
    static_assert(putils::is_member_function_ptr<decltype(&Obj::f)>());
    SUCCEED();
}

TEST(IsMemberFunctionPtrTest, Const) {
    static_assert(putils::is_member_function_ptr<decltype(&Obj::fconst)>());
    SUCCEED();
}

TEST(IsMemberFunctionPtrTest, Noexcept) {
    static_assert(putils::is_member_function_ptr<decltype(&Obj::fnoexcept)>());
    SUCCEED();
}

TEST(IsMemberFunctionPtrTest, ConstNoexcept) {
    static_assert(putils::is_member_function_ptr<decltype(&Obj::fconstnoexcept)>());
    SUCCEED();
}

TEST(IsMemberFunctionPtrTest, Attribute) {
    static_assert(!putils::is_member_function_ptr<decltype(&Obj::i)>());
    SUCCEED();
}

TEST(IsMemberFunctionPtrTest, Pointer) {
    static_assert(!putils::is_member_function_ptr<int *>());
    SUCCEED();
}

TEST(IsMemberFunctionPtrTest, Function) {
    static_assert(!putils::is_member_function_ptr<void (*)()>());
    SUCCEED();
}
