// gtest
#include <gtest/gtest.h>

// meta
#include "putils/meta/traits/has_nested_type.hpp"

struct yes {
    struct nested {};
};

struct no {
};

putils_nested_type_detector(nested);

TEST(has_nested_type, true) {
    static_assert(has_nested_type_Nested<yes>());
    SUCCEED();
}

TEST(has_nested_type, false) {
    static_assert(!has_nested_type_Nested<no>());
    SUCCEED();
}
