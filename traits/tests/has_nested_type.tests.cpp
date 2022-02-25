#include <gtest/gtest.h>
#include "meta/traits/has_nested_type.hpp"

struct Yes {
    struct Nested {};
};

struct No {
};

putils_nested_type_detector(Nested);

TEST(has_nested_type, true) {
    static_assert(has_nested_type_Nested<Yes>());
    SUCCEED();
}

TEST(has_nested_type, false) {
    static_assert(!has_nested_type_Nested<No>());
    SUCCEED();
}
