#include "solution.h"

#include <gtest/gtest.h>

using namespace p677;

TEST(MapSum, basic) {
    MapSum m;

    m.insert("apple", 3);
    EXPECT_EQ(m.sum("ap"), 3);

    m.insert("app", 2);
    EXPECT_EQ(m.sum("ap"), 5);
}

TEST(MapSum, absent_prefix) {
    MapSum m;

    m.insert("a", 3);
    EXPECT_EQ(m.sum("ap"), 0);

    m.insert("b", 2);
    EXPECT_EQ(m.sum("a"), 3);
}
