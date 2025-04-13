#include "solution.h"

#include <gtest/gtest.h>

using namespace p542;

struct TestCase {
    std::vector<std::vector<int>> input;
    std::vector<std::vector<int>> expct;
};

TEST(test_suite_name, t1) {
    Solution s;

    TestCase t{
        {
            {0, 0, 0},
            {0, 1, 0},
            {0, 0, 0},
        },
        {
            {0, 0, 0},
            {0, 1, 0},
            {0, 0, 0},
        },
    };

    EXPECT_EQ(s.updateMatrix(t.input), t.expct);
}

TEST(test_suite_name, t2) {
    Solution s;

    TestCase t{
        {
            {0, 0, 0},
            {0, 1, 0},
            {1, 1, 1},
        },
        {
            {0, 0, 0},
            {0, 1, 0},
            {1, 2, 1},
        },
    };

    EXPECT_EQ(s.updateMatrix(t.input), t.expct);
}
