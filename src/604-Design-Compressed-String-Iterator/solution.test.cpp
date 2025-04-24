#include "solution.h"

#include <gtest/gtest.h>

using namespace p604;

TEST(iterator, basic) {
    StringIterator s("a1b2c3");

    EXPECT_EQ(s.next(), 'a');
    EXPECT_EQ(s.next(), 'b');
    EXPECT_EQ(s.next(), 'b');
    EXPECT_EQ(s.next(), 'c');
    EXPECT_EQ(s.next(), 'c');
    EXPECT_EQ(s.next(), 'c');
    EXPECT_FALSE(s.hasNext());
    EXPECT_EQ(s.next(), ' ');
}
