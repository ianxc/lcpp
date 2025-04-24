#include "solution.h"

#include <gtest/gtest.h>

using namespace p1784;

using TestCase = std::pair<std::string, bool>;

TEST(test_suite_name, char_by_char_solution) {
    Solution s;

    std::vector<TestCase> cases{{"1001", false}, {"110", true}};

    for (auto& [binary_string, expected] : cases) {
        std::cout << binary_string << '\n';
        EXPECT_EQ(s.checkOnesSegment(binary_string), expected);
    }
}

TEST(test_suite_name, easy_solution) {
    EasySolution s;

    std::vector<TestCase> cases{{"1001", false}, {"110", true}};

    for (auto& [binary_string, expected] : cases) {
        std::cout << binary_string << '\n';
        EXPECT_EQ(s.checkOnesSegment(binary_string), expected);
    }
}
