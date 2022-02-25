#include <gtest/gtest.h>
#include "meta/traits/indexed_type.hpp"

template<typename T>
using Result = std::is_same<float, std::decay_t<putils::indexed_type<T>>>;

TEST(indexed_type, array) {
    static_assert(Result<float[2]>());
    SUCCEED();
}

TEST(indexed_type, pointer) {
    static_assert(Result<float *>());
    SUCCEED();
}

TEST(indexed_type, vector) {
    static_assert(Result<std::vector<float>>());
    SUCCEED();
}

TEST(indexed_type, map) {
    static_assert(Result<std::map<int, float>>());
    SUCCEED();
}
