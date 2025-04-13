#include "solution.h"

#include <gtest/gtest.h>

using namespace p2233;

using Input = std::vector<int>;

TEST(maximumProduct, t1) {
    Solution s;
    Input v{0, 4};

    EXPECT_EQ(s.maximumProduct(v, 5), 20);
}

TEST(maximumProduct, t1a) {
    Solution s;
    Input v{0, 5};

    EXPECT_EQ(s.maximumProduct(v, 4), 20);
}

TEST(maximumProduct, t2) {
    Solution s;
    Input v2{6, 3, 3, 2};

    EXPECT_EQ(s.maximumProduct(v2, 2), 216);
}
