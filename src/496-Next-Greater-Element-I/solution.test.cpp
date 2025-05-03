#include "solution.h"

#include <gtest/gtest.h>

using namespace p496;

namespace {

struct TestCase {
    std::vector<int> nums1;
    std::vector<int> nums2;
    std::vector<int> expected;
};

std::vector<TestCase> cases{
    {{4, 1, 2}, {1, 3, 4, 2}, {-1, 3, -1}},
    {{2, 4}, {1, 2, 3, 4}, {3, -1}},
};

}  // namespace

TEST(test_suite_name, test_name) {
    Solution s;
    for (auto& [nums1, nums2, expected] : cases) {
        auto actual = s.nextGreaterElement(nums1, nums2);

        EXPECT_EQ(actual, expected);
    }
}
