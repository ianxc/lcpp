#include "solution.h"

#include <gtest/gtest.h>

using namespace p2042;

TEST(test_suite_name, test_name) {
    Solution s;

    EXPECT_EQ(s.areNumbersAscending("a puppy has 2 eyes 4 legs"), true);
    EXPECT_EQ(s.areNumbersAscending("a puppy has 4 eyes 2 legs"), false);
    EXPECT_EQ(s.areNumbersAscending("12 a 23 45 100 b cz"), true);
    EXPECT_EQ(s.areNumbersAscending("hello world 5 x 5"), false);
}
