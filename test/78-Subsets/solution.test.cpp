#include "solution.h"

#include <gtest/gtest.h>

TEST(test_suite_name, test_name) {
    Solution s;

    std::vector input{1, 2, 3};
    std::vector<std::vector<int>> expected{{},     {1}, {1, 2}, {1, 2, 3},
                                           {1, 3}, {2}, {2, 3}, {3}};

    EXPECT_EQ(s.subsets(input), expected);
}
