#pragma once

#include <vector>

namespace p78 {

class Solution {
  public:
    std::vector<std::vector<int>> subsets(std::vector<int>& nums) {
        const int n = nums.size();
        std::vector<std::vector<int>> saved_subsets;

        auto backtrack = [&, n](const auto& self, int curr_idx,
                                std::vector<int>& curr_nums) -> void {
            saved_subsets.push_back(curr_nums);
            if (curr_idx == n) {
                return;
            }

            for (auto i = curr_idx; i < n; i++) {
                curr_nums.push_back(nums[i]);
                self(self, i + 1, curr_nums);
                curr_nums.pop_back();
            }
        };

        std::vector<int> v;
        backtrack(backtrack, 0, v);
        return saved_subsets;
    }
};

}  // namespace p78
