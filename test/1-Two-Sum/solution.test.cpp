#include "solution.h"

#include <gtest/gtest.h>

#include <icecream.hpp>
#include <vector>

TEST(TwoSum, Test1) {
  Solution s;
  auto v = std::vector{1, 2, 3};
  EXPECT_EQ(s.two_sum(v, 4), std::pair(0, 2));
}

TEST(TwoSum, Test2) {
  Solution2 s;
  auto v = std::vector{1, 2, 3};
  auto exp = std::vector{0, 2};
  auto res = s.twoSum(v, 4);
  EXPECT_EQ(res, exp);
}
