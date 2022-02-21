#include <gtest/gtest.h>
#include "meta/traits/is_unstreamable.hpp"

TEST(IsUnunstreamableTest, String) {
    static_assert(putils::is_unstreamable<std::istream, std::string>());
    SUCCEED();
}

TEST(IsUnunstreamableTest, Vector) {
    static_assert(!putils::is_unstreamable<std::istream, std::vector<bool>>());
    SUCCEED();
}

TEST(IsUnunstreamableTest, Scalar) {
    static_assert(putils::is_unstreamable<std::istream, int>());
    SUCCEED();
}

TEST(IsUnunstreamableTest, NotStream) {
    static_assert(!putils::is_unstreamable<int, std::string>());
    SUCCEED();
}
