#pragma once

#include <stack>
#include <type_traits>
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
        static constexpr auto get_left_child =
            [](const TreeNode *root) -> const TreeNode * { return root->left; };
        static constexpr auto get_right_child =
            [](const TreeNode *root) -> const TreeNode * {
            return root->right;
        };

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
        static_assert(std::is_invocable_r_v<const TreeNode *, BoundChildGetter,
                                            const TreeNode *>,
                      "BoundChildGetter must conform to signature");
        static_assert(
            std::is_invocable_r_v<const TreeNode *, InternalChildGetter,
                                  const TreeNode *>,
            "InternalChildGetter must conform to signature");

        std::stack<const TreeNode *> stack;
        bool seen_leaf = false;

        if (bound_root != nullptr) {
            stack.push(bound_root);
        }

        while (!stack.empty()) {
            const auto *curr = stack.top();
            stack.pop();

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
                stack.push(ic);
            }

            if (bc != nullptr) {
                stack.push(bc);
            }
        }
    }
};

}  // namespace p545
