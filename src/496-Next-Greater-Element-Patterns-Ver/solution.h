#pragma once

#include <stack>
#include <vector>

namespace p496_patterns_ver {

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

}  // namespace p496_patterns_ver
