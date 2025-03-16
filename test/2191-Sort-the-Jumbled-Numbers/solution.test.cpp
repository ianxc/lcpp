#include "solution.h"

#include <gtest/gtest.h>

TEST(test_suite_name, test_name) {
    Solution s;
    auto mapping = std::vector{8, 9, 4, 0, 2, 1, 3, 5, 7, 6};
    auto nums = std::vector{991, 338, 38};
    auto exp = std::vector<int>{338, 38, 991};
    EXPECT_EQ(s.sortJumbled(mapping, nums), exp);
}
