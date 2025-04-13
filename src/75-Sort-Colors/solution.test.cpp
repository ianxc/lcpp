#include "solution.h"

#include <gtest/gtest.h>

using namespace p75;

TEST(sortColors, t1) {
    Solution s;
    std::vector input{2, 0, 2, 1, 1, 0};
    std::vector expct{0, 0, 1, 1, 2, 2};

    s.sortColors(input);

    EXPECT_EQ(input, expct);
}

TEST(sortColors, t2) {
    Solution s;
    std::vector input{2, 0, 1};
    std::vector expct{0, 1, 2};

    s.sortColors(input);

    EXPECT_EQ(input, expct);
}
