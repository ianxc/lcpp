#include "solution.h"

#include <gtest/gtest.h>

#include <icecream.hpp>

TEST(Suite1, add_double_2nd) {
    IC();
    IC(add_double_2nd(2, 3));
    ASSERT_EQ(add_double_2nd(2, 3), 8);
    ASSERT_EQ(add_double_2nd(3, 2), 7);
}
