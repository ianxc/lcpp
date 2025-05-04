#include "solution.h"

#include <gtest/gtest.h>

using namespace p503;

namespace {

struct TestCase {
    std::vector<int> nums;
    std::vector<int> expected;
};

std::vector<TestCase> cases{{{1, 2, 1}, {2, -1, 2}},
                            {{1, 2, 3, 4, 3}, {2, 3, 4, -1, 4}}};

}  // namespace

TEST(test_suite_name, test_name) {
    Solution s;

    for (auto& [nums, expected] : cases) {
        EXPECT_EQ(s.nextGreaterElements(nums), expected);
    }
}
