#pragma once

#include <vector>

namespace p545 {

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

/*
 * Idea:
 * pre-order left side, only add node if it's a leaf node OR we have not yet
 * seen the first leaf node.
 *
 * then do pre-order traversal on the right side following the same strategy.
 * combine root value + left-order + reverse(right-order)
 */
class Solution {
  public:
    std::vector<int> boundaryOfBinaryTree(TreeNode *root) {
        std::vector<int> left_bound{root->val};
        left_boundary(left_bound, root->left);
        std::vector<int> right_bound;
        right_boundary(right_bound, root->right);

        // combine left with reverse of right.
        left_bound.insert(left_bound.end(), right_bound.crbegin(),
                          right_bound.crend());
        return left_bound;
    }

  private:
    void right_boundary(std::vector<int> &right_bound, const TreeNode *right) {
        std::vector<const TreeNode *> right_stack;
        auto seen_right_leaf = false;
        if (right != nullptr) {
            right_stack.push_back(right);
        }

        while (!right_stack.empty()) {
            const auto *curr = right_stack.back();
            right_stack.pop_back();

            if (curr->left == nullptr && curr->right == nullptr) {
                right_bound.push_back(curr->val);
                seen_right_leaf = true;
                continue;
            } else if (!seen_right_leaf) {
                right_bound.push_back(curr->val);
            }

            if (curr->left != nullptr) {
                right_stack.push_back(curr->left);
            }
            if (curr->right != nullptr) {
                right_stack.push_back(curr->right);
            }
        }
    }

    void left_boundary(std::vector<int> &left_bound, const TreeNode *left) {
        std::vector<const TreeNode *> left_stack;
        auto seen_left_leaf = false;
        if (left != nullptr) {
            left_stack.push_back(left);
        }

        while (!left_stack.empty()) {
            const auto *curr = left_stack.back();
            left_stack.pop_back();

            if (curr->left == nullptr && curr->right == nullptr) {
                left_bound.push_back(curr->val);
                seen_left_leaf = true;
                // not needed, but put just to skip further checks.
                continue;
            } else if (!seen_left_leaf) {
                left_bound.push_back(curr->val);
            }

            if (curr->right != nullptr) {
                left_stack.push_back(curr->right);
            }
            if (curr->left != nullptr) {
                left_stack.push_back(curr->left);
            }
        }
    }
};

}  // namespace p545
