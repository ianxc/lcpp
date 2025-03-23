#include "solution.h"

#include <gtest/gtest.h>

namespace {

struct scenario {
    std::vector<int> input;
    bool expected;
};

scenario t1{{3, 2, 3, 2, 2, 2}, true};
scenario t2{{1, 2, 3, 4}, false};
// note how we can make pairs that sum to 7 = 2^3 - 1.
scenario t3{{1, 2, 5, 6}, false};
scenario t4{{1, 2, 7, 8}, false};
scenario t5{{1, 2, 5, 6, 3, 4}, false};

}  // namespace

TEST(Solution, all) {
    Solution s;

    for (auto sc : {&t1, &t2, &t3, &t4, &t5}) {
        EXPECT_EQ(s.divideArray(sc->input), sc->expected);
    }
}

TEST(WrongXorSolution, all) {
    WrongXorSolution s;

    for (auto sc : {&t1, &t2, &t4, &t5}) {
        EXPECT_EQ(s.divideArray(sc->input), sc->expected);
    }

    // wrong behaviour
    EXPECT_TRUE(s.divideArray(t3.input));
}
