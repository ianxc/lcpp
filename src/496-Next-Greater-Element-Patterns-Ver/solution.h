#pragma once

#include <stack>
#include <vector>

namespace p496_patterns_ver {

/**
 * Approach: monotonically decreasing stack (smallest values at topic of stack)
 * stores the valid remanining candidates for the next greater value.
 */
class IterateReverseSolution {
  public:
    std::vector<int> find_solution(const std::vector<int>& nums) {
        const int n = nums.size();
        std::vector<int> next_greater_results(n, -1);
        std::stack<int> next_greater_candidates;
        for (int i = n - 1; i >= 0; i--) {
            while (!next_greater_candidates.empty() &&
                   nums[i] >= next_greater_candidates.top()) {
                next_greater_candidates.pop();
            }

            if (!next_greater_candidates.empty()) {
                next_greater_results[i] = next_greater_candidates.top();
            }

            next_greater_candidates.push(nums[i]);
        }

        return next_greater_results;
    }
};

/**
 * Approach: monotonically increasing stack that stores previous values for
 * which we have not yet found a greater element for (actually, store the
 * index).
 */
class IterateForwardSolution {
  public:
    std::vector<int> find_solution(const std::vector<int>& nums) {
        const int n = nums.size();
        std::vector<int> next_greater_results(n, -1);
        std::stack<int> greater_to_find;
        for (int i = 0; i < n; i++) {
            while (!greater_to_find.empty() &&
                   nums[greater_to_find.top()] < nums[i]) {
                next_greater_results[greater_to_find.top()] = nums[i];
                greater_to_find.pop();
            }
            greater_to_find.push(i);
        }

        return next_greater_results;
    }
};

}  // namespace p496_patterns_ver
