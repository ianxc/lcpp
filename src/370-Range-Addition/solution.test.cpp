#include "solution.h"

#include <gtest/gtest.h>

using namespace p370;

namespace {

struct TestCase {
    int length;
    std::vector<std::vector<int>> updates;
    std::vector<int> expected;
};

std::vector<TestCase> cases;

}  // namespace

TEST(test_suite_name, test_name) {
    Solution s;

    for (auto& [length, updates, expected] : cases) {
        EXPECT_EQ(s.getModifiedArray(length, updates), expected);
    }
}
