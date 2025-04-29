#include "solution.h"

#include <gtest/gtest.h>

using namespace p370;

namespace {

struct TestCase {
    int length;
    std::vector<std::vector<int>> updates;
    std::vector<int> expected;
};

std::vector<TestCase> cases{
    {5, {{1, 3, 2}, {2, 4, 3}, {0, 2, -2}}, {-2, 0, 3, 5, 3}},
};

}  // namespace

TEST(test_suite_name, test_name) {
    Solution s;

    for (auto& [length, updates, expected] : cases) {
        // std::printf("struct: %p, updates: %p\n", (void*)&(cases[0].updates),
        //             (void*)&updates);
        EXPECT_EQ(s.getModifiedArray(length, updates), expected);
    }
}
