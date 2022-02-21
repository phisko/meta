#include <gtest/gtest.h>
#include "meta/traits/indexed_type.hpp"

template<typename T>
using Result = std::is_same<float, std::decay_t<putils::indexed_type<T>>>;

TEST(IndexedTypeTest, Array) {
    static_assert(Result<float[2]>());
    SUCCEED();
}

TEST(IndexedTypeTest, Pointer) {
    static_assert(Result<float *>());
    SUCCEED();
}

TEST(IndexedTypeTest, Vector) {
    static_assert(Result<std::vector<float>>());
    SUCCEED();
}

TEST(IndexedTypeTest, Map) {
    static_assert(Result<std::map<int, float>>());
    SUCCEED();
}
