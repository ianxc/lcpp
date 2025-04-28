#include "solution.h"

#include <gtest/gtest.h>

using namespace p339;

TEST(test_suite_name, test_name) {
    Solution s;

    std::vector input{NestedInteger(123)};

    EXPECT_EQ(s.depthSum(input), 123);
}
