#include "solution.h"

#include <gtest/gtest.h>

using namespace p496_patterns_ver;

namespace {

struct TestCase {
    std::vector<int> nums;
    std::vector<int> expected;
};

std::vector<TestCase> cases{
    {.nums = {1, 1, 2, 3, 2, 3, 2, 4}, .expected = {2, 2, 3, 4, 3, 4, 4, -1}},
};

}  // namespace

TEST(IterateReverseSolutionTest, test_name) {
    IterateReverseSolution s;

    for (auto& [nums, expected] : cases) {
        EXPECT_EQ(s.find_solution(nums), expected);
    }
}
