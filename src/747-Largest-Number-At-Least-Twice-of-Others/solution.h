#pragma once

#include <vector>

namespace p747 {

class Solution {
  public:
    int dominantIndex(std::vector<int>& nums) {
        auto [best1, best2] =
            nums[0] > nums[1] ? std::pair{0, 1} : std::pair{1, 0};

        auto n = static_cast<int>(nums.size());
        for (int i = 2; i < n; i++) {
            if (nums[i] >= nums[best1]) {
                best2 = best1;
                best1 = i;
            } else if (nums[i] > nums[best2]) {
                best2 = i;
            }
        }

        return nums[best1] >= 2 * nums[best2] ? best1 : -1;
    }
};

}  // namespace p747
