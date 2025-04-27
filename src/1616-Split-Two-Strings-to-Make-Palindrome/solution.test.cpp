#include "solution.h"

#include <gtest/gtest.h>

using namespace p1616;

namespace {

struct TestCase {
    std::string a;
    std::string b;
    bool expected;
};

std::vector<TestCase> cases{
    {"x", "y", true},
    {"aejbaalflrmkswrydwdkdwdyrwskmrlfqizjezd",
     "uvebspqckawkhbrtlqwblfwzfptanhiglaabjea", true},
    {"pvhmupgqeltozftlmfjjde", "yjgpzbezspnnpszebzmhvp", true},
    {"xbdef", "xecab", false},
};

}  // namespace

TEST(test_suite_name, test_name) {
    Solution s;

    for (auto& [a, b, expected] : cases) {
        ASSERT_EQ(s.checkPalindromeFormation(a, b), expected);
    }
}
