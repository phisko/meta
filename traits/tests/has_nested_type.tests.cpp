#include <gtest/gtest.h>
#include "meta/traits/has_nested_type.hpp"

struct Yes {
    struct Nested {};
};

struct No {
};

putils_nested_type_detector(Nested);

TEST(HasNestedType, True) {
    static_assert(has_nested_type_Nested<Yes>());
    SUCCEED();
}

TEST(HasNestedType, False) {
    static_assert(!has_nested_type_Nested<No>());
    SUCCEED();
}
