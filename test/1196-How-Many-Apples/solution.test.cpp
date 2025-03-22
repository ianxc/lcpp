#include "solution.h"

#include <gtest/gtest.h>

TEST(test_suite_name, test_name) {
    Solution s;

    std::vector in1{100, 200, 150, 1000};
    EXPECT_EQ(s.maxNumberOfApples(in1), 4);

    std::vector<int> in2{5000, 10};
    EXPECT_EQ(s.maxNumberOfApples(in2), 1);
}
