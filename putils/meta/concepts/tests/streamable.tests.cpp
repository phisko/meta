// gtest
#include <gtest/gtest.h>

// meta
#include "putils/meta/concepts/streamable.hpp"

TEST(streamable, string) {
    static_assert(putils::streamable<std::string, std::ostream>);
    SUCCEED();
}

TEST(streamable, vector) {
    static_assert(!putils::streamable<std::vector<bool>, std::ostream>);
    SUCCEED();
}

TEST(streamable, scalar) {
    static_assert(putils::streamable<int, std::ostream>);
    SUCCEED();
}

TEST(streamable, not_stream) {
    static_assert(!putils::streamable<int, std::string>);
    SUCCEED();
}
