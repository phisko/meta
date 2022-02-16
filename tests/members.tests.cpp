#include <gtest/gtest.h>
#include "meta/members.hpp"

struct Obj {
    double d = 1024;
    int i = 42;
    using Member = decltype(&Obj::i);
};

TEST(MembersTest, MemberType) {
    static_assert(std::is_same<int, PUTILS_MEMBER_TYPE(Obj, Obj::Member)>());
    SUCCEED();
}

TEST(MembersTest, MemberTypeMacro) {
    static_assert(std::is_same<int, putils::MemberType<Obj::Member>>());
    SUCCEED();
}

TEST(MembersTest, ObjectType) {
    static_assert(std::is_same<Obj, putils::ObjectType<Obj::Member>>());
    SUCCEED();
}

TEST(MembersTest, MemberOffset) {
    const auto offset = putils::member_offset(&Obj::i);
    const Obj obj;
    EXPECT_EQ((const char *)&obj + offset, (const char *)&obj.i);
}