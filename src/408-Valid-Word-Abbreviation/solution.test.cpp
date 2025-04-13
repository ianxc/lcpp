#include "solution.h"

#include <gtest/gtest.h>

using namespace p408;

TEST(Solution, test_name) {
    Solution s;

    EXPECT_FALSE(s.validWordAbbreviation("apple", "a2e"));
    EXPECT_TRUE(s.validWordAbbreviation("apple", "a3e"));
    EXPECT_TRUE(s.validWordAbbreviation("internationalization", "i12iz4n"));

    EXPECT_TRUE(s.validWordAbbreviation("internationalization", "i5a11o1"));
    EXPECT_FALSE(s.validWordAbbreviation("substitution", "s0ubstitution"));

    EXPECT_FALSE(s.validWordAbbreviation("substitution", "s55n"));
}
