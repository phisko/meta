#include <gtest/gtest.h>
#include "meta/traits/is_streamable.hpp"

TEST(is_streamable, string) {
    static_assert(putils::is_streamable<std::ostream, std::string>());
    SUCCEED();
}

TEST(is_streamable, vector) {
    static_assert(!putils::is_streamable<std::ostream, std::vector<bool>>());
    SUCCEED();
}

TEST(is_streamable, scalar) {
    static_assert(putils::is_streamable<std::ostream, int>());
    SUCCEED();
}

TEST(is_streamable, not_stream) {
    static_assert(!putils::is_streamable<int, std::string>());
    SUCCEED();
}
