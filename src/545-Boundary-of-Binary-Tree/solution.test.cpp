#include "solution.h"

#include <gtest/gtest.h>

using namespace p545;

TEST(areNumbersAscending, LC_1) {
    Solution s;

    TreeNode input{1, nullptr,
                   new TreeNode{2, new TreeNode{3}, new TreeNode{4}}};
    std::vector exp = {1, 3, 4, 2};

    EXPECT_EQ(s.boundaryOfBinaryTree(&input), exp);
}

TEST(areNumbersAscending, LC_2) {
    Solution s;

    auto input = TreeNode{
        1,
        new TreeNode(2, new TreeNode(4),
                     new TreeNode(5, new TreeNode(7), new TreeNode(8))),
        new TreeNode(3, new TreeNode(6, new TreeNode(9), new TreeNode(10)),
                     nullptr)};

    std::vector exp = {1, 2, 4, 7, 8, 9, 10, 6, 3};

    EXPECT_EQ(s.boundaryOfBinaryTree(&input), exp);
}
