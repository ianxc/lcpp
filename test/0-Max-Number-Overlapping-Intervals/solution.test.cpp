#include "solution.h"

#include <gtest/gtest.h>

using namespace p0_max_num_overlapping_intervals;

using Intervals = std::vector<std::pair<int, int>>;

TEST(s1, simple) {
    Solution s;

    Intervals v{{1, 5}, {2, 4}, {6, 7}};

    EXPECT_EQ(s.max_num_overlapping_intervals(v), 2);
}

TEST(s1, book) {
    Solution s;

    Intervals v{{1, 3}, {2, 6}, {4, 8}, {6, 7}, {5, 7}};

    EXPECT_EQ(s.max_num_overlapping_intervals(v), 3);
}
