#include "solution.h"

#include <gtest/gtest.h>

#include <vector>

using namespace p747;

TEST(test_suite_name, test_name) {
    Solution s;

    using scenario = std::pair<std::vector<int>, int>;

    scenario s1{{3, 6, 1, 0}, 1};
    scenario s2{{1, 2, 3, 4}, -1};

    EXPECT_EQ(s.dominantIndex(s1.first), s1.second);
    EXPECT_EQ(s.dominantIndex(s2.first), s2.second);
}
