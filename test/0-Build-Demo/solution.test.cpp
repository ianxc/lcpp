#include "../../src/0-Build-Demo/solution.h"

#include "gtest/gtest.h"

TEST(Suite1, add_double_2nd) {
  ASSERT_EQ(add_double_2nd(2, 3), 8);
  ASSERT_EQ(add_double_2nd(3, 2), 7);
}
