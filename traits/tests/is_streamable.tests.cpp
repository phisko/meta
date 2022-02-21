#include <gtest/gtest.h>
#include "meta/traits/is_streamable.hpp"

TEST(IsStreamableTest, String) {
    static_assert(putils::is_streamable<std::ostream, std::string>());
    SUCCEED();
}

TEST(IsStreamableTest, Vector) {
    static_assert(!putils::is_streamable<std::ostream, std::vector<bool>>());
    SUCCEED();
}

TEST(IsStreamableTest, Scalar) {
    static_assert(putils::is_streamable<std::ostream, int>());
    SUCCEED();
}

TEST(IsStreamableTest, NotStream) {
    static_assert(!putils::is_streamable<int, std::string>());
    SUCCEED();
}
