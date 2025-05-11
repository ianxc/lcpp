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

    ~TreeNode() noexcept {
        delete this->left;
        delete this->right;
    }
};

/*
 * Idea:
 * pre-order left side, only add node if it's a leaf node OR we have not yet
 * seen the first leaf node.
 *
 * then do pre-order traversal on the right side following the same
 * strategy. combine root value + left-order + reverse(right-order)
 */
class Solution {
  public:
    std::vector<int> boundaryOfBinaryTree(TreeNode *root) {
        auto get_left_child = [](const TreeNode *root) { return root->left; };
        auto get_right_child = [](const TreeNode *root) { return root->right; };

        std::vector<int> left_bound{root->val};
        traverse_boundary(left_bound, get_left_child(root), get_left_child,
                          get_right_child);

        std::vector<int> right_bound;
        traverse_boundary(right_bound, get_right_child(root), get_right_child,
                          get_left_child);

        // combine left with reverse of right.
        left_bound.insert(left_bound.end(), right_bound.crbegin(),
                          right_bound.crend());
        return left_bound;
    }

  private:
    // yep, separate template type parameters are required.
    template <typename BoundChildGetter, typename InternalChildGetter>
    void traverse_boundary(std::vector<int> &boundary,
                           const TreeNode *bound_root,
                           BoundChildGetter &&get_bound_child,
                           InternalChildGetter &&get_internal_child) {
        std::vector<const TreeNode *> stack;
        bool seen_leaf = false;

        if (bound_root != nullptr) {
            stack.push_back(bound_root);
        }

        while (!stack.empty()) {
            const auto *curr = stack.back();
            stack.pop_back();

            const TreeNode *bc = get_bound_child(curr);
            const TreeNode *ic = get_internal_child(curr);

            if (ic == nullptr && bc == nullptr) {
                boundary.push_back(curr->val);
                seen_leaf = true;
                // not needed, but put just to skip further checks.
                continue;
            } else if (!seen_leaf) {
                boundary.push_back(curr->val);
            }

            if (ic != nullptr) {
                stack.push_back(ic);
            }

            if (bc != nullptr) {
                stack.push_back(bc);
            }
        }
    }
};

}  // namespace p545
