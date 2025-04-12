#pragma once

#include <functional>
#include <vector>

namespace p78 {

class Solution {
  public:
    std::vector<std::vector<int>> subsets(std::vector<int>& nums) {
        const int n = nums.size();
        std::vector<std::vector<int>> res;

        // cannot use auto inline lambda prior to C++23 as it's recursive.
        std::function<void(int, std::vector<int>&)> backtrack =
            [&, n](int curr_idx, std::vector<int>& curr_nums) -> void {
            res.push_back(curr_nums);
            if (curr_idx == n) {
                return;
            }

            for (auto i = curr_idx; i < n; i++) {
                curr_nums.push_back(nums[i]);
                backtrack(i + 1, curr_nums);
                curr_nums.pop_back();
            }
        };

        std::vector<int> v;
        backtrack(0, v);
        return res;
    }
};

}  // namespace p78
