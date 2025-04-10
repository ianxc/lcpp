#include "solution.h"

#include <gtest/gtest.h>

using namespace p1196;

TEST(Solution1, basic) {
    Solution s;

    std::vector in1{100, 200, 150, 1000};
    EXPECT_EQ(s.maxNumberOfApples(in1), 4);

    std::vector<int> in2{5000, 10};
    EXPECT_EQ(s.maxNumberOfApples(in2), 1);
}

TEST(HeapSolution, basic) {
    HeapSolution s;

    std::vector in1{100, 200, 150, 1000};
    EXPECT_EQ(s.maxNumberOfApples(in1), 4);

    std::vector<int> in2{5000, 10};
    EXPECT_EQ(s.maxNumberOfApples(in2), 1);
}
