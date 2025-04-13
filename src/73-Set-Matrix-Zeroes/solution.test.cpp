#include "solution.h"

#include <gtest/gtest.h>

using namespace p73;

TEST(TwoPassLinearSumSpace, self) {
    TwoPassLinearSumSpaceSolution s;

    std::vector<std::vector<int>> m{
        {0, 1, 1, 0},
        {1, 1, 1, 1},
        {1, 0, 1, 1},
    };
    std::vector<std::vector<int>> expected{
        {0, 0, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0},
    };

    s.setZeroes(m);

    ASSERT_EQ(m, expected);
}

TEST(InPlace, self) {
    InPlaceSolution s;

    std::vector<std::vector<int>> m{
        {0, 1, 1, 0},
        {1, 1, 1, 1},
        {1, 0, 1, 1},
    };
    std::vector<std::vector<int>> expected{
        {0, 0, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0},
    };

    s.setZeroes(m);

    ASSERT_EQ(m, expected);
}
