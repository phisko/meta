#include <gtest/gtest.h>
#include "meta/traits/is_specialization.hpp"

TEST(IsSpecialization, Vector) {
    static_assert(putils::is_specialization<std::vector<bool>, std::vector>());
    SUCCEED();
}

TEST(IsSpecialization, Map) {
    static_assert(putils::is_specialization<std::map<int, bool>, std::map>());
    SUCCEED();
}

TEST(IsSpecialization, False) {
    static_assert(!putils::is_specialization<std::map<int, bool>, std::vector>());
    SUCCEED();
}