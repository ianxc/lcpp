#include "solution.h"

#include <gtest/gtest.h>

#include <tuple>

using namespace p0_template;

TEST(test_suite_name, test_name) {
    using TestCase = std::tuple<std::vector<int>, std::vector<int>, int>;

    Solution s;
    std::vector<TestCase> cases{
        {{1, 2, 3}, {2}, 1},
        {{1, 2, 3, 4}, {1, 4}, 1},
        {{1, 5}, {2}, 3},
    };

    for (auto& [houses, heaters, expected] : cases) {
        EXPECT_EQ(s.findRadius(houses, heaters), expected);
    }
}
